//
// Created by Екатерина on 23.11.2022.
//

#ifndef SRC_TESTREADERACCOUNTS_H
#define SRC_TESTREADERACCOUNTS_H

#include <Entities/DBAccount/AccountSpecifications/GetAccount.h>
#include <Entities/DBAccount/AccountFilters/ByAccountIDFilter.h>
#include <Entities/DBAccount/ReaderAccount/ReaderAccountRepository.h>
#include <Entities/DBAccount/ReaderAccount/ReaderAccountSpecifications/GetReaderAccount.h>
#include "../ObjectMothers/ReaderAccountsObjectMother.h"
#include "../Stubs/ReaderAccountSpecificationStub.h"
BOOST_AUTO_TEST_CASE(TestGetReaderAccountSpecificationByID){
        // arrange
        ReaderAccountsObjectMother objectMother;
        std::vector<ReaderAccount> initial = objectMother.getDefault();
        std::vector<ReaderAccount> forCheck = objectMother.getWithID(initial, 1);

        TestingSession ts;
        ts.initReaderAccountTable(initial);
        std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
        std::shared_ptr<GetReaderAccount> getAccSpec  = std::shared_ptr<GetReaderAccount>(new GetReaderAccount(std::vector<std::shared_ptr<AccountFilter>> ({std::shared_ptr<AccountFilter>(new ByAccountIDFilter(1))})));
        std::shared_ptr<ReaderAccountSpecification> aspec = std::shared_ptr<ReaderAccountSpecification>(getAccSpec);

        // act
        aspec->exec(session);

        // assert
        BOOST_CHECK_EQUAL(ts.getSelectedReaderAccountTable() == forCheck, true);
}
BOOST_AUTO_TEST_CASE(TestGetReaderAccountSpecificationByLogin){
        // arrange
        ReaderAccountsObjectMother objectMother;
        std::vector<ReaderAccount> initial = objectMother.getDefault();
        std::vector<ReaderAccount> forCheck = objectMother.getWithLogin(initial, "l1");

        TestingSession ts;
        ts.initReaderAccountTable(initial);
        std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
        std::shared_ptr<GetReaderAccount> getAccSpec  = std::shared_ptr<GetReaderAccount>(new GetReaderAccount(std::vector<std::shared_ptr<AccountFilter>> ({std::shared_ptr<AccountFilter>(new ByLoginFilter("l1"))})));
        std::shared_ptr<ReaderAccountSpecification> aspec = std::shared_ptr<ReaderAccountSpecification>(getAccSpec);

        // act
        aspec->exec(session);

        // assert
        BOOST_CHECK_EQUAL(ts.getSelectedReaderAccountTable() == forCheck, true);
}
BOOST_AUTO_TEST_CASE(TestReaderAccountQueryClassic){
        // arrange
        ReaderAccountsObjectMother objectMother;
        std::vector<ReaderAccount> initial = objectMother.getDefault();
        std::vector<ReaderAccount> forCheck = objectMother.getWithLogin(initial, "l1");

        TestingSession ts;
        ts.initReaderAccountTable(initial);
        std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
        std::shared_ptr<GetReaderAccount> getAccSpec  = std::shared_ptr<GetReaderAccount>(new GetReaderAccount(std::vector<std::shared_ptr<AccountFilter>> ({std::shared_ptr<AccountFilter>(new ByLoginFilter("l1"))})));
        std::shared_ptr<ReaderAccountSpecification> aspec = std::shared_ptr<ReaderAccountSpecification>(getAccSpec);
        ReaderAccountRepository repo;
        // act
        repo.query(session, aspec);

        // assert
        BOOST_CHECK_EQUAL(ts.getSelectedReaderAccountTable() == forCheck, true);
}
BOOST_AUTO_TEST_CASE(TestReaderAccountQueryLondon){
        // arrange
        ReaderAccountsObjectMother objectMother;
        std::vector<ReaderAccount> initial = objectMother.getDefault();
        std::vector<ReaderAccount> forCheck = objectMother.getWithLogin(initial, "l1");

        TestingSession ts;
        ts.initReaderAccountTable(initial);
        std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
        std::shared_ptr<ReaderAccountSpecification> aspec = std::shared_ptr<ReaderAccountSpecification>(new ReaderAccountSpecificationStub());
        ReaderAccountRepository repo;
        // act
        repo.query(session, aspec);

        // assert
        BOOST_CHECK_EQUAL(ts.getSelectedReaderAccountTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestReaderAccountAdd){
        // arrange
        ReaderAccountsObjectMother objectMother;
        std::vector<ReaderAccount> initial = objectMother.getDefault();
        std::shared_ptr<Account> account = std::shared_ptr<Account>( new Account("l6", "p6", "admin", "n6"));
        account->setID(1);
        ReaderAccount acc(account, "123");
        std::vector<ReaderAccount> forCheck = objectMother.getWithAdd(initial, acc);
        std::shared_ptr<ReaderAccount> aacc = std::shared_ptr<ReaderAccount>(new ReaderAccount(account, "123"));

        TestingSession ts;
        ts.initReaderAccountTable(initial);
        std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
        ReaderAccountRepository repo;
        // act
        repo.addAccount(session, aacc);

        // assert
        BOOST_CHECK_EQUAL(ts.getSelectedReaderAccountTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestReaderAccountUpd){
        // arrange
        ReaderAccountsObjectMother objectMother;
        std::vector<ReaderAccount> initial = objectMother.getDefault();
        std::shared_ptr<Account> account = std::shared_ptr<Account>( new Account("l6", "p6", "admin", "n6"));
        account->setID(5);
        ReaderAccount acc(account, "1234");
        std::vector<ReaderAccount> forCheck = objectMother.getWithUpd(initial, 5, acc);
        std::shared_ptr<ReaderAccount> aacc = std::shared_ptr<ReaderAccount>(new ReaderAccount(account, "1234"));

        TestingSession ts;
        ts.initReaderAccountTable(initial);
        std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
        ReaderAccountRepository repo;
        // act
        repo.updateAccount(session, aacc);

        // assert
        BOOST_CHECK_EQUAL(ts.getSelectedReaderAccountTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestReaderAccountDel){
        // arrange
        ReaderAccountsObjectMother objectMother;
        std::vector<ReaderAccount> initial = objectMother.getDefault();
        std::vector<ReaderAccount> forCheck = objectMother.getWithDel(initial, 5);

        TestingSession ts;
        ts.initReaderAccountTable(initial);
        std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
        ReaderAccountRepository repo;
        // act
        repo.removeAccount(session, 5);

        // assert
        BOOST_CHECK_EQUAL(ts.getSelectedReaderAccountTable() == forCheck, true);
}
#endif //SRC_TESTREADERACCOUNTS_H
