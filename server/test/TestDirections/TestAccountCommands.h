//
// Created by Екатерина on 23.11.2022.
//

#ifndef SRC_TESTACCOUNTCOMMANDS_H
#define SRC_TESTACCOUNTCOMMANDS_H

#include <DataAccessFacade/Commands/AccountCommands/UpdateAccounts/UpdateAdminAccountCommand.h>
#include <DataAccessFacade/Commands/AccountCommands/UpdateAccounts/UpdateLibrarianAccountCommand.h>
#include <DataAccessFacade/Commands/AccountCommands/UpdateAccounts/UpdateReaderAccountCommand.h>
#include <DataAccessFacade/Commands/AccountCommands/DeleteAccounts/DeleteAdminAccountCommand.h>
#include <DataAccessFacade/Commands/AccountCommands/DeleteAccounts/DeleteLibrarianAccountCommand.h>
#include <DataAccessFacade/Commands/AccountCommands/DeleteAccounts/DeleteReaderAccountCommand.h>
#include "DataAccessFacade/Commands/AccountCommands/AuthCommand/AuthCommand.h"
#include "DataAccessFacade/Commands/AccountCommands/RegisterCommand/RegisterAdminCommand.h"
#include "DataAccessFacade/Commands/AccountCommands/RegisterCommand/RegisterLibrarianCommand.h"
#include "DataAccessFacade/Commands/AccountCommands/RegisterCommand/RegisterReaderCommand.h"

#include "../test/Mocks/AccountRepositoryMock.h"
#include "../test/Mocks/AdminAccountRepositoryMock.h"
#include "../test/Mocks/LibrarianAccountRepositoryMock.h"
#include "../test/Mocks/ReaderAccountRepositoryMock.h"
BOOST_AUTO_TEST_CASE(TestAuthCommand){
    // arrange
    std::vector<std::string> checkSeq = {"query"};
    auto mock = new AccountRepositoryMock(true);
    std::shared_ptr<IAccountRepository> repositoryMock = std::shared_ptr<IAccountRepository> (mock);
    std::vector<std::shared_ptr<Account>> accs({std::shared_ptr<Account> (new Account("l", "p", "r", "n"))});
    AuthCommand command = AuthCommand(repositoryMock, "l", accs);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);
    // assert
    BOOST_CHECK_EQUAL(mock->getSequence() == checkSeq, true);
}
BOOST_AUTO_TEST_CASE(TestRegisterAdminCommand){
    // arrange
    std::vector<std::string> checkSeq = {"add"};
    auto mock = new AdminAccountRepositoryMock(true);
    std::shared_ptr<IAdminAccountRepository> repositoryMock = std::shared_ptr<IAdminAccountRepository> (mock);
    std::shared_ptr<Account> acc(new Account("l", "p", "r", "n"));
    std::shared_ptr<AdminAccount> aacc(new AdminAccount(acc));
    RegisterAdminCommand command = RegisterAdminCommand(repositoryMock, aacc);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);
    // assert
    BOOST_CHECK_EQUAL(mock->getSequence() == checkSeq, true);
}
BOOST_AUTO_TEST_CASE(TestRegisterLibrarianCommand){
    // arrange
    std::vector<std::string> checkSeq = {"add"};
    auto mock = new LibrarianAccountRepositoryMock(true);
    std::shared_ptr<ILibrarianAccountRepository> repositoryMock = std::shared_ptr<ILibrarianAccountRepository> (mock);
    std::shared_ptr<Account> acc(new Account("l", "p", "r", "n"));
    std::shared_ptr<LibrarianAccount> lacc(new LibrarianAccount(acc, 1));
    RegisterLibrarianCommand command = RegisterLibrarianCommand(repositoryMock, lacc);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);
    // assert
    BOOST_CHECK_EQUAL(mock->getSequence() == checkSeq, true);
}
BOOST_AUTO_TEST_CASE(TestRegisterReaderCommand){
    // arrange
    std::vector<std::string> checkSeq = {"add"};
    auto mock = new ReaderAccountRepositoryMock(true);
    std::shared_ptr<IReaderAccountRepository> repositoryMock = std::shared_ptr<IReaderAccountRepository> (mock);
    std::shared_ptr<Account> acc(new Account("l", "p", "r", "n"));
    std::shared_ptr<ReaderAccount> lacc(new ReaderAccount(acc, "123"));
    RegisterReaderCommand command = RegisterReaderCommand(repositoryMock, lacc);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);
    // assert
    BOOST_CHECK_EQUAL(mock->getSequence() == checkSeq, true);
}
BOOST_AUTO_TEST_CASE(TestUpdateAdminCommand){
    // arrange
    std::vector<std::string> checkAccountSeq = {"query"};
    auto accountMock = new AccountRepositoryMock(true);
    std::shared_ptr<IAccountRepository> repositoryAccountMock = std::shared_ptr<IAccountRepository> (accountMock);

    std::vector<std::string> checkSeq = {"update"};
    auto mock = new AdminAccountRepositoryMock(true);
    std::shared_ptr<IAdminAccountRepository> repositoryMock = std::shared_ptr<IAdminAccountRepository> (mock);

    std::shared_ptr<Account> acc(new Account("l", "p", "r", "n"));
    std::shared_ptr<AdminAccount> aacc(new AdminAccount(acc));
    UpdateAdminAccountCommand command = UpdateAdminAccountCommand(repositoryMock, repositoryAccountMock, aacc);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);
    // assert
    BOOST_CHECK_EQUAL((mock->getSequence() == checkSeq) && (accountMock->getSequence() == checkAccountSeq), true);
}
BOOST_AUTO_TEST_CASE(TestUpdateLibrarianCommand){
    // arrange
    std::vector<std::string> checkAccountSeq = {"query"};
    auto accountMock = new AccountRepositoryMock(true);
    std::shared_ptr<IAccountRepository> repositoryAccountMock = std::shared_ptr<IAccountRepository> (accountMock);

    std::vector<std::string> checkSeq = {"update"};
    auto mock = new LibrarianAccountRepositoryMock(true);
    std::shared_ptr<ILibrarianAccountRepository> repositoryMock = std::shared_ptr<ILibrarianAccountRepository> (mock);

    std::shared_ptr<Account> acc(new Account("l", "p", "r", "n"));
    std::shared_ptr<LibrarianAccount> lacc(new LibrarianAccount(acc, 1));
    UpdateLibrarianAccountCommand command = UpdateLibrarianAccountCommand(repositoryMock, repositoryAccountMock, lacc);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);
    // assert
    BOOST_CHECK_EQUAL((mock->getSequence() == checkSeq) && (accountMock->getSequence() == checkAccountSeq), true);
}
BOOST_AUTO_TEST_CASE(TestUpdateReaderCommand){
    // arrange
    std::vector<std::string> checkAccountSeq = {"query"};
    auto accountMock = new AccountRepositoryMock(true);
    std::shared_ptr<IAccountRepository> repositoryAccountMock = std::shared_ptr<IAccountRepository> (accountMock);

    std::vector<std::string> checkSeq = {"update"};
    auto mock = new ReaderAccountRepositoryMock(true);
    std::shared_ptr<IReaderAccountRepository> repositoryMock = std::shared_ptr<IReaderAccountRepository> (mock);

    std::shared_ptr<Account> acc(new Account("l", "p", "r", "n"));
    std::shared_ptr<ReaderAccount> lacc(new ReaderAccount(acc, "123"));
    UpdateReaderAccountCommand command = UpdateReaderAccountCommand(repositoryMock, repositoryAccountMock, lacc);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);
    // assert
    BOOST_CHECK_EQUAL((mock->getSequence() == checkSeq) && (accountMock->getSequence() == checkAccountSeq), true);
}
BOOST_AUTO_TEST_CASE(TestDeleteAdminCommand){
    // arrange
    std::vector<std::string> checkAccountSeq = {"query"};
    auto accountMock = new AccountRepositoryMock(true);
    std::shared_ptr<IAccountRepository> repositoryAccountMock = std::shared_ptr<IAccountRepository> (accountMock);

    std::vector<std::string> checkSeq = {"remove"};
    auto mock = new AdminAccountRepositoryMock(true);
    std::shared_ptr<IAdminAccountRepository> repositoryMock = std::shared_ptr<IAdminAccountRepository> (mock);

    DeleteAdminAccountCommand command = DeleteAdminAccountCommand(repositoryMock, repositoryAccountMock, 1);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);
    // assert
    BOOST_CHECK_EQUAL((mock->getSequence() == checkSeq) && (accountMock->getSequence() == checkAccountSeq), true);
}
BOOST_AUTO_TEST_CASE(TestDeleteLibrarianCommand){
    // arrange
    std::vector<std::string> checkAccountSeq = {"query"};
    auto accountMock = new AccountRepositoryMock(true);
    std::shared_ptr<IAccountRepository> repositoryAccountMock = std::shared_ptr<IAccountRepository> (accountMock);

    std::vector<std::string> checkSeq = {"remove"};
    auto mock = new LibrarianAccountRepositoryMock(true);
    std::shared_ptr<ILibrarianAccountRepository> repositoryMock = std::shared_ptr<ILibrarianAccountRepository> (mock);

    DeleteLibrarianAccountCommand command = DeleteLibrarianAccountCommand(repositoryMock, repositoryAccountMock, 1);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);
    // assert
    BOOST_CHECK_EQUAL((mock->getSequence() == checkSeq) && (accountMock->getSequence() == checkAccountSeq), true);
}
BOOST_AUTO_TEST_CASE(TestDeleteReaderCommand){
    // arrange
    std::vector<std::string> checkAccountSeq = {"query"};
    auto accountMock = new AccountRepositoryMock(true);
    std::shared_ptr<IAccountRepository> repositoryAccountMock = std::shared_ptr<IAccountRepository> (accountMock);

    std::vector<std::string> checkSeq = {"remove"};
    auto mock = new ReaderAccountRepositoryMock(true);
    std::shared_ptr<IReaderAccountRepository> repositoryMock = std::shared_ptr<IReaderAccountRepository> (mock);

    DeleteReaderAccountCommand command = DeleteReaderAccountCommand(repositoryMock, repositoryAccountMock, 1);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);
    // assert
    BOOST_CHECK_EQUAL((mock->getSequence() == checkSeq) && (accountMock->getSequence() == checkAccountSeq), true);
}
#endif //SRC_TESTACCOUNTCOMMANDS_H
