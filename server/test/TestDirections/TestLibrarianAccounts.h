//
// Created by Екатерина on 23.11.2022.
//

#ifndef SRC_TESTLIBRARIANACCOUNTS_H
#define SRC_TESTLIBRARIANACCOUNTS_H

#include <Entities/DBAccount/AccountSpecifications/GetAccount.h>
#include <Entities/DBAccount/AccountFilters/ByAccountIDFilter.h>
#include <Entities/DBAccount/LibrarianAccount/LibrarianAccountRepository.h>
#include <Entities/DBAccount/LibrarianAccount/LibrarianAccountSpecifications/GetLibrarianAccount.h>
#include "../ObjectMothers/LibrarianAccountsObjectMother.h"
#include "../Stubs/LibrarianAccountSpecificationStub.h"
BOOST_AUTO_TEST_CASE(TestGetLibrarianAccountSpecificationByID){
        // arrange
        LibrarianAccountsObjectMother objectMother;
        std::vector<LibrarianAccount> initial = objectMother.getDefault();
        std::vector<LibrarianAccount> forCheck = objectMother.getWithID(initial, 1);

        TestingSession ts;
        ts.initLibrarianAccountTable(initial);
        std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
        std::shared_ptr<GetLibrarianAccount> getAccSpec  = std::shared_ptr<GetLibrarianAccount>(new GetLibrarianAccount(std::vector<std::shared_ptr<AccountFilter>> ({std::shared_ptr<AccountFilter>(new ByAccountIDFilter(1))})));
        std::shared_ptr<LibrarianAccountSpecification> aspec = std::shared_ptr<LibrarianAccountSpecification>(getAccSpec);

        // act
        aspec->exec(session);

        // assert
        BOOST_CHECK_EQUAL(ts.getSelectedLibrarianAccountTable() == forCheck, true);
}
BOOST_AUTO_TEST_CASE(TestGetLibrarianAccountSpecificationByLogin){
        // arrange
        LibrarianAccountsObjectMother objectMother;
        std::vector<LibrarianAccount> initial = objectMother.getDefault();
        std::vector<LibrarianAccount> forCheck = objectMother.getWithLogin(initial, "l1");

        TestingSession ts;
        ts.initLibrarianAccountTable(initial);
        std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
        std::shared_ptr<GetLibrarianAccount> getAccSpec  = std::shared_ptr<GetLibrarianAccount>(new GetLibrarianAccount(std::vector<std::shared_ptr<AccountFilter>> ({std::shared_ptr<AccountFilter>(new ByLoginFilter("l1"))})));
        std::shared_ptr<LibrarianAccountSpecification> aspec = std::shared_ptr<LibrarianAccountSpecification>(getAccSpec);

        // act
        aspec->exec(session);

        // assert
        BOOST_CHECK_EQUAL(ts.getSelectedLibrarianAccountTable() == forCheck, true);
}
BOOST_AUTO_TEST_CASE(TestLibrarianAccountQueryClassic){
        // arrange
        LibrarianAccountsObjectMother objectMother;
        std::vector<LibrarianAccount> initial = objectMother.getDefault();
        std::vector<LibrarianAccount> forCheck = objectMother.getWithLogin(initial, "l1");

        TestingSession ts;
        ts.initLibrarianAccountTable(initial);
        std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
        std::shared_ptr<GetLibrarianAccount> getAccSpec  = std::shared_ptr<GetLibrarianAccount>(new GetLibrarianAccount(std::vector<std::shared_ptr<AccountFilter>> ({std::shared_ptr<AccountFilter>(new ByLoginFilter("l1"))})));
        std::shared_ptr<LibrarianAccountSpecification> aspec = std::shared_ptr<LibrarianAccountSpecification>(getAccSpec);
        LibrarianAccountRepository repo;
        // act
        repo.query(session, aspec);

        // assert
        BOOST_CHECK_EQUAL(ts.getSelectedLibrarianAccountTable() == forCheck, true);
}
BOOST_AUTO_TEST_CASE(TestLibrarianAccountQueryLondon){
        // arrange
        LibrarianAccountsObjectMother objectMother;
        std::vector<LibrarianAccount> initial = objectMother.getDefault();
        std::vector<LibrarianAccount> forCheck = objectMother.getWithLogin(initial, "l1");

        TestingSession ts;
        ts.initLibrarianAccountTable(initial);
        std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
        std::shared_ptr<LibrarianAccountSpecification> aspec = std::shared_ptr<LibrarianAccountSpecification>(new LibrarianAccountSpecificationStub());
        LibrarianAccountRepository repo;
        // act
        repo.query(session, aspec);

        // assert
        BOOST_CHECK_EQUAL(ts.getSelectedLibrarianAccountTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestLibrarianAccountAdd){
        // arrange
        LibrarianAccountsObjectMother objectMother;
        std::vector<LibrarianAccount> initial = objectMother.getDefault();
        std::shared_ptr<Account> account = std::shared_ptr<Account>( new Account("l6", "p6", "admin", "n6"));
        account->setID(1);
        LibrarianAccount acc(account, 4);
        std::vector<LibrarianAccount> forCheck = objectMother.getWithAdd(initial, acc);
        std::shared_ptr<LibrarianAccount> aacc = std::shared_ptr<LibrarianAccount>(new LibrarianAccount(account, 4));

        TestingSession ts;
        ts.initLibrarianAccountTable(initial);
        std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
        LibrarianAccountRepository repo;
        // act
        repo.addAccount(session, aacc);

        // assert
        BOOST_CHECK_EQUAL(ts.getSelectedLibrarianAccountTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestLibrarianAccountUpd){
        // arrange
        LibrarianAccountsObjectMother objectMother;
        std::vector<LibrarianAccount> initial = objectMother.getDefault();
        std::shared_ptr<Account> account = std::shared_ptr<Account>( new Account("l6", "p6", "admin", "n6"));
        account->setID(5);
        LibrarianAccount acc(account, 4);
        std::vector<LibrarianAccount> forCheck = objectMother.getWithUpd(initial, 5, acc);
        std::shared_ptr<LibrarianAccount> aacc = std::shared_ptr<LibrarianAccount>(new LibrarianAccount(account, 4));

        TestingSession ts;
        ts.initLibrarianAccountTable(initial);
        std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
        LibrarianAccountRepository repo;
        // act
        repo.updateAccount(session, aacc);

        // assert
        BOOST_CHECK_EQUAL(ts.getSelectedLibrarianAccountTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestLibrarianAccountDel){
        // arrange
        LibrarianAccountsObjectMother objectMother;
        std::vector<LibrarianAccount> initial = objectMother.getDefault();
        std::vector<LibrarianAccount> forCheck = objectMother.getWithDel(initial, 5);

        TestingSession ts;
        ts.initLibrarianAccountTable(initial);
        std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
        LibrarianAccountRepository repo;
        // act
        repo.removeAccount(session, 5);

        // assert
        BOOST_CHECK_EQUAL(ts.getSelectedLibrarianAccountTable() == forCheck, true);
}
#endif //SRC_TESTLIBRARIANACCOUNTS_H
