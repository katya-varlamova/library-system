//
// Created by Екатерина on 27.11.2022.
//

#ifndef SRC_TESTBOOKCOMMANDS_H
#define SRC_TESTBOOKCOMMANDS_H
#include "DataAccessFacade/Commands/BookCommands/GetFreeBooksCommand.h"
#include "DataAccessFacade/Commands/BookCommands/GetBooksByLoginCommand.h"
#include "DataAccessFacade/Commands/BookCommands/AddBooksCommand.h"
#include "DataAccessFacade/Commands/BookCommands/UpdateBookCommand.h"
#include "DataAccessFacade/Commands/BookCommands/DeleteBooksCommand.h"

#include "../test/Mocks/BookRepositoryMock.h"

BOOST_AUTO_TEST_CASE(TestGetBooksCommand){
        // arrange
        std::vector<std::string> checkSeq = {"query"};
        auto mock = new BookRepositoryMock(true);
        std::shared_ptr<IBookRepository> repositoryMock = std::shared_ptr<IBookRepository> (mock);
        std::vector<std::shared_ptr<Book>> books;
        std::vector<std::shared_ptr<Filter>> filters;
        GetFreeBooksCommand command = GetFreeBooksCommand(repositoryMock,books, filters);
        TestingSession ts;
        std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
        // act
        command.execute(session);
        // assert
        BOOST_CHECK_EQUAL(mock->getSequence() == checkSeq, true);
}
BOOST_AUTO_TEST_CASE(TestGetLoginBooksCommand){
    // arrange
    std::vector<std::string> checkSeq = {"query"};
    auto mock = new BookRepositoryMock(true);
    std::shared_ptr<IBookRepository> repositoryMock = std::shared_ptr<IBookRepository> (mock);
    std::vector<std::shared_ptr<Book>> books;
    std::vector<std::shared_ptr<Filter>> filters;
    GetBooksByLoginCommand command = GetBooksByLoginCommand(repositoryMock,books, filters);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);
    // assert
    BOOST_CHECK_EQUAL(mock->getSequence() == checkSeq, true);
}
BOOST_AUTO_TEST_CASE(TestAddBooksCommandPos){
    // arrange
    std::vector<std::string> checkBookSeq = {"add"};
    auto mock = new BookRepositoryMock(true);
    std::shared_ptr<IBookRepository> repositoryMock = std::shared_ptr<IBookRepository> (mock);

    std::vector<std::string> checkLibSeq = {"query"};
    auto libMock = new LibraryRepositoryMock(true);
    std::shared_ptr<ILibraryRepository> libRepositoryMock = std::shared_ptr<ILibraryRepository> (libMock);

    std::shared_ptr<Book> b (new Book("name", "author"));
    std::vector<std::shared_ptr<Book>> books = {b};
    AddBooksCommand command = AddBooksCommand(repositoryMock, libRepositoryMock, books);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);

    // assert
    BOOST_CHECK_EQUAL((mock->getSequence() == checkBookSeq) && (libMock->getSequence() == checkLibSeq), true);
}
BOOST_AUTO_TEST_CASE(TestAddBooksCommandNeg){
    // arrange
    std::vector<std::string> checkBookSeq = {};
    auto mock = new BookRepositoryMock(true);
    std::shared_ptr<IBookRepository> repositoryMock = std::shared_ptr<IBookRepository> (mock);

    std::vector<std::string> checkLibSeq = {"query"};
    auto libMock = new LibraryRepositoryMock(false);
    std::shared_ptr<ILibraryRepository> libRepositoryMock = std::shared_ptr<ILibraryRepository> (libMock);

    std::shared_ptr<Book> b (new Book("name", "author"));
    std::vector<std::shared_ptr<Book>> books = {b};
    AddBooksCommand command = AddBooksCommand(repositoryMock, libRepositoryMock, books);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    bool exc = false;
    // act
    try {
        command.execute(session);
    }
    catch (DatabaseException)
    {
        exc = true;
    }

    // assert
    BOOST_CHECK_EQUAL(exc && (mock->getSequence() == checkBookSeq) && (libMock->getSequence() == checkLibSeq), true);
}
BOOST_AUTO_TEST_CASE(TestUpdateBooksCommandPos){
    // arrange
    std::vector<std::string> checkBookSeq = {"query", "update"};
    auto mock = new BookRepositoryMock(true);
    std::shared_ptr<IBookRepository> repositoryMock = std::shared_ptr<IBookRepository> (mock);

    std::vector<std::string> checkLibSeq = {"query"};
    auto libMock = new LibraryRepositoryMock(true);
    std::shared_ptr<ILibraryRepository> libRepositoryMock = std::shared_ptr<ILibraryRepository> (libMock);

    std::shared_ptr<Book> book (new Book("name", "author"));
    UpdateBookCommand command = UpdateBookCommand(repositoryMock, libRepositoryMock, book);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);

    // assert
    BOOST_CHECK_EQUAL((mock->getSequence() == checkBookSeq) && (libMock->getSequence() == checkLibSeq), true);
}
BOOST_AUTO_TEST_CASE(TestUpdateBooksCommandNeg1){
    // arrange
    std::vector<std::string> checkBookSeq = {};
    auto mock = new BookRepositoryMock(true);
    std::shared_ptr<IBookRepository> repositoryMock = std::shared_ptr<IBookRepository> (mock);

    std::vector<std::string> checkLibSeq = {"query"};
    auto libMock = new LibraryRepositoryMock(false);
    std::shared_ptr<ILibraryRepository> libRepositoryMock = std::shared_ptr<ILibraryRepository> (libMock);

    std::shared_ptr<Book> book (new Book("name", "author"));
    UpdateBookCommand command = UpdateBookCommand(repositoryMock, libRepositoryMock, book);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    bool exc = false;
    // act
    try {
        command.execute(session);
    }
    catch (DatabaseException)
    {
        exc = true;
    }

    // assert
    BOOST_CHECK_EQUAL(exc && (mock->getSequence() == checkBookSeq) && (libMock->getSequence() == checkLibSeq), true);
}
BOOST_AUTO_TEST_CASE(TestUpdateBooksCommandNeg2){
    // arrange
    std::vector<std::string> checkBookSeq = {"query"};
    auto mock = new BookRepositoryMock(false);
    std::shared_ptr<IBookRepository> repositoryMock = std::shared_ptr<IBookRepository> (mock);

    std::vector<std::string> checkLibSeq = {"query"};
    auto libMock = new LibraryRepositoryMock(true);
    std::shared_ptr<ILibraryRepository> libRepositoryMock = std::shared_ptr<ILibraryRepository> (libMock);

    std::shared_ptr<Book> book (new Book("name", "author"));
    UpdateBookCommand command = UpdateBookCommand(repositoryMock, libRepositoryMock, book);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));

    bool exc = false;
    // act
    try {
        command.execute(session);
    }
    catch (DatabaseException)
    {
        exc = true;
    }

    // assert
    BOOST_CHECK_EQUAL(exc && (mock->getSequence() == checkBookSeq) && (libMock->getSequence() == checkLibSeq), true);
}
BOOST_AUTO_TEST_CASE(TestDeleteBooksCommandPos){
    // arrange
    std::vector<std::string> checkBookSeq = {"query", "remove"};
    auto mock = new BookRepositoryMock(true);
    std::shared_ptr<IBookRepository> repositoryMock = std::shared_ptr<IBookRepository> (mock);

    DeleteBooksCommand command = DeleteBooksCommand(repositoryMock, 1);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);

    // assert
    BOOST_CHECK_EQUAL(mock->getSequence() == checkBookSeq, true);
}
BOOST_AUTO_TEST_CASE(TestDeleteBooksCommandNeg){
    // arrange
    std::vector<std::string> checkBookSeq = {"query"};
    auto mock = new BookRepositoryMock(false);
    std::shared_ptr<IBookRepository> repositoryMock = std::shared_ptr<IBookRepository> (mock);

    DeleteBooksCommand command = DeleteBooksCommand(repositoryMock, 1);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    bool exc = false;
    // act
    try {
        command.execute(session);
    }
    catch (DatabaseException)
    {
        exc = true;
    }

    // assert
    BOOST_CHECK_EQUAL(exc && (mock->getSequence() == checkBookSeq), true);
}

#endif //SRC_TESTBOOKCOMMANDS_H
