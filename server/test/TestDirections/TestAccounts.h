//
// Created by Екатерина on 21.11.2022.
//

#ifndef SRC_TESTACCOUNTS_H
#define SRC_TESTACCOUNTS_H

#include <Entities/DBAccount/AccountSpecifications/GetAccount.h>
#include <Entities/DBAccount/AccountFilters/ByAccountIDFilter.h>
#include <Entities/DBAccount/AccountRepository.h>
#include "../ObjectMothers/AccountsObjectMother.h"
#include "../Stubs/AccountSpecificationStub.h"
BOOST_AUTO_TEST_CASE(TestGetAccountSpecificationByID){
    // arrange
    AccountsObjectMother objectMother;
    std::vector<Account> initial = objectMother.getDefault();
    std::vector<Account> forCheck = objectMother.getWithID(initial, 1);

    TestingSession ts;
    ts.initAccountTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetAccount> getAccSpec  = std::shared_ptr<GetAccount>(new GetAccount(std::vector<std::shared_ptr<AccountFilter>> ({std::shared_ptr<AccountFilter>(new ByAccountIDFilter(1))})));
    std::shared_ptr<AccountSpecification> aspec = std::shared_ptr<AccountSpecification>(getAccSpec);

    // act
    aspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedAccountTable() == forCheck, true);
}
BOOST_AUTO_TEST_CASE(TestGetAccountSpecificationByLogin){
    // arrange
    AccountsObjectMother objectMother;
    std::vector<Account> initial = objectMother.getDefault();
    std::vector<Account> forCheck = objectMother.getWithLogin(initial, "l1");

    TestingSession ts;
    ts.initAccountTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetAccount> getAccSpec  = std::shared_ptr<GetAccount>(new GetAccount(std::vector<std::shared_ptr<AccountFilter>> ({std::shared_ptr<AccountFilter>(new ByLoginFilter("l1"))})));
    std::shared_ptr<AccountSpecification> aspec = std::shared_ptr<AccountSpecification>(getAccSpec);

    // act
    aspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedAccountTable() == forCheck, true);
}
BOOST_AUTO_TEST_CASE(TestAccountQueryClassic){
    // arrange
    AccountsObjectMother objectMother;
    std::vector<Account> initial = objectMother.getDefault();
    std::vector<Account> forCheck = objectMother.getWithLogin(initial, "l1");

    TestingSession ts;
    ts.initAccountTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetAccount> getAccSpec  = std::shared_ptr<GetAccount>(new GetAccount(std::vector<std::shared_ptr<AccountFilter>> ({std::shared_ptr<AccountFilter>(new ByLoginFilter("l1"))})));
    std::shared_ptr<AccountSpecification> aspec = std::shared_ptr<AccountSpecification>(getAccSpec);
    AccountRepository repo;
    // act
    repo.query(session, aspec);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedAccountTable() == forCheck, true);
}
BOOST_AUTO_TEST_CASE(TestAccountQueryLondon){
    // arrange
    AccountsObjectMother objectMother;
    std::vector<Account> initial = objectMother.getDefault();
    std::vector<Account> forCheck = objectMother.getWithLogin(initial, "l1");

    TestingSession ts;
    ts.initAccountTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<AccountSpecification> aspec = std::shared_ptr<AccountSpecification>(new AccountSpecificationStub());
    AccountRepository repo;
    // act
    repo.query(session, aspec);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedAccountTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestAccountAdd){
    // arrange
    AccountsObjectMother objectMother;
    std::vector<Account> initial = objectMother.getDefault();
    Account account("l6", "p6", "admin", "n6");
    std::shared_ptr<Account> acc = std::shared_ptr<Account>(new Account("l6", "p6", "admin", "n6"));
    std::vector<Account> forCheck = objectMother.getWithAdd(initial, account);

    TestingSession ts;
    ts.initAccountTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    AccountRepository repo;
    // act
    repo.addAccount(session, acc);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedAccountTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestAccountUpd){
    // arrange
    AccountsObjectMother objectMother;
    std::vector<Account> initial = objectMother.getDefault();
    Account account("l6", "p6", "admin", "n6");
    account.setID(5);
    std::shared_ptr<Account> acc = std::shared_ptr<Account>(new Account("l6", "p6", "admin", "n6"));
    acc->setID(5);
    std::vector<Account> forCheck = objectMother.getWithAdd(initial, account);

    TestingSession ts;
    ts.initAccountTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    AccountRepository repo;
    // act
    repo.updateAccount(session, acc);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedAccountTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestAccountDel){
    // arrange
    AccountsObjectMother objectMother;
    std::vector<Account> initial = objectMother.getDefault();
    std::vector<Account> forCheck = objectMother.getWithDel(initial, 1);

    TestingSession ts;
    ts.initAccountTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    AccountRepository repo;
    // act
    repo.removeAccount(session, 1);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedAccountTable() == forCheck, true);
}
#endif //SRC_TESTACCOUNTS_H
