//
// Created by Екатерина on 21.11.2022.
//

#ifndef SRC_TESTADMINACCOUNTS_H
#define SRC_TESTADMINACCOUNTS_H

#include <Entities/DBAccount/AccountSpecifications/GetAccount.h>
#include <Entities/DBAccount/AccountFilters/ByAccountIDFilter.h>
#include <Entities/DBAccount/AdminAccount/AdminAccountRepository.h>
#include <Entities/DBAccount/AdminAccount/AdminAccountSpecifications/GetAdminAccount.h>
#include "../ObjectMothers/AdminAccountsObjectMother.h"
#include "../Stubs/AdminAccountSpecificationStub.h"
BOOST_AUTO_TEST_CASE(TestGetAdminAccountSpecificationByID){
        // arrange
        AdminAccountsObjectMother objectMother;
        std::vector<AdminAccount> initial = objectMother.getDefault();
        std::vector<AdminAccount> forCheck = objectMother.getWithID(initial, 1);

        TestingSession ts;
        ts.initAdminAccountTable(initial);
        std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
        std::shared_ptr<GetAdminAccount> getAccSpec  = std::shared_ptr<GetAdminAccount>(new GetAdminAccount(std::vector<std::shared_ptr<AccountFilter>> ({std::shared_ptr<AccountFilter>(new ByAccountIDFilter(1))})));
        std::shared_ptr<AdminAccountSpecification> aspec = std::shared_ptr<AdminAccountSpecification>(getAccSpec);

        // act
        aspec->exec(session);

        // assert
        BOOST_CHECK_EQUAL(ts.getSelectedAdminAccountTable() == forCheck, true);
}
BOOST_AUTO_TEST_CASE(TestGetAdminAccountSpecificationByLogin){
    // arrange
    AdminAccountsObjectMother objectMother;
    std::vector<AdminAccount> initial = objectMother.getDefault();
    std::vector<AdminAccount> forCheck = objectMother.getWithLogin(initial, "l1");

    TestingSession ts;
    ts.initAdminAccountTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetAdminAccount> getAccSpec  = std::shared_ptr<GetAdminAccount>(new GetAdminAccount(std::vector<std::shared_ptr<AccountFilter>> ({std::shared_ptr<AccountFilter>(new ByLoginFilter("l1"))})));
    std::shared_ptr<AdminAccountSpecification> aspec = std::shared_ptr<AdminAccountSpecification>(getAccSpec);

    // act
    aspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedAdminAccountTable() == forCheck, true);
}
BOOST_AUTO_TEST_CASE(TestAdminAccountQueryClassic){
    // arrange
    AdminAccountsObjectMother objectMother;
    std::vector<AdminAccount> initial = objectMother.getDefault();
    std::vector<AdminAccount> forCheck = objectMother.getWithLogin(initial, "l1");

    TestingSession ts;
    ts.initAdminAccountTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetAdminAccount> getAccSpec  = std::shared_ptr<GetAdminAccount>(new GetAdminAccount(std::vector<std::shared_ptr<AccountFilter>> ({std::shared_ptr<AccountFilter>(new ByLoginFilter("l1"))})));
    std::shared_ptr<AdminAccountSpecification> aspec = std::shared_ptr<AdminAccountSpecification>(getAccSpec);
    AdminAccountRepository repo;
    // act
    repo.query(session, aspec);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedAdminAccountTable() == forCheck, true);
}
BOOST_AUTO_TEST_CASE(TestAdminAccountQueryLondon){
    // arrange
    AdminAccountsObjectMother objectMother;
    std::vector<AdminAccount> initial = objectMother.getDefault();
    std::vector<AdminAccount> forCheck = objectMother.getWithLogin(initial, "l1");

    TestingSession ts;
    ts.initAdminAccountTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<AdminAccountSpecification> aspec = std::shared_ptr<AdminAccountSpecification>(new AdminAccountSpecificationStub());
    AdminAccountRepository repo;
    // act
    repo.query(session, aspec);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedAdminAccountTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestAdminAccountAdd){
    // arrange
    AdminAccountsObjectMother objectMother;
    std::vector<AdminAccount> initial = objectMother.getDefault();
    std::shared_ptr<Account> account = std::shared_ptr<Account>( new Account("l6", "p6", "admin", "n6"));
    account->setID(1);
    AdminAccount acc(account);
    std::vector<AdminAccount> forCheck = objectMother.getWithAdd(initial, acc);
    std::shared_ptr<AdminAccount> aacc = std::shared_ptr<AdminAccount>(new AdminAccount(account));

    TestingSession ts;
    ts.initAdminAccountTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    AdminAccountRepository repo;
    // act
    repo.addAccount(session, aacc);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedAdminAccountTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestAdminAccountUpd){
    // arrange
    AdminAccountsObjectMother objectMother;
    std::vector<AdminAccount> initial = objectMother.getDefault();
    std::shared_ptr<Account> account = std::shared_ptr<Account>( new Account("l6", "p6", "admin", "n6"));
    account->setID(5);
    AdminAccount acc(account);
    std::vector<AdminAccount> forCheck = objectMother.getWithUpd(initial, 5, acc);
    std::shared_ptr<AdminAccount> aacc = std::shared_ptr<AdminAccount>(new AdminAccount(account));

    TestingSession ts;
    ts.initAdminAccountTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    AdminAccountRepository repo;
    // act
    repo.updateAccount(session, aacc);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedAdminAccountTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestAdminAccountDel){
    // arrange
    AdminAccountsObjectMother objectMother;
    std::vector<AdminAccount> initial = objectMother.getDefault();
    std::vector<AdminAccount> forCheck = objectMother.getWithDel(initial, 5);

    TestingSession ts;
    ts.initAdminAccountTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    AdminAccountRepository repo;
    // act
    repo.removeAccount(session, 5);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedAdminAccountTable() == forCheck, true);
}
#endif //SRC_TESTADMINACCOUNTS_H
