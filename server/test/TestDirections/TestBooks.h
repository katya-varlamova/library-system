//
// Created by Екатерина on 20.11.2022.
//

#ifndef SRC_TESTBOOKS_H
#define SRC_TESTBOOKS_H
#include <boost/test/unit_test.hpp>
#include <Entities/DBBook/BookSpecifications/GetBooks.h>
#include <Entities/DBBook/BookFilters/ByBookNameFilter.h>
#include <Entities/DBBook/BookFilters/ByAuthorFilter.h>
#include <Entities/DBBook/BookFilters/ByBookIDFilter.h>
#include <Entities/DBAccount/AccountFilters/ByLoginFilter.h>
#include <Entities/DBBook/BookSpecifications/GetFreeBooks.h>
#include <Entities/DBBook/BookRepository.h>
#include "../ObjectMothers/BooksObjectMother.h"
#include "../Stubs/BookSpecificationStub.h"

BOOST_AUTO_TEST_CASE(TestGetBookSpecificationByName){
    // arrange
    BooksObjectMother objectMother;
    std::vector<Book> initial = objectMother.getDefault();
    std::vector<Book> forCheck = objectMother.getWithName(initial, "book1");

    TestingSession ts;
    ts.initBookTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetBooks> getBookSpec  = std::shared_ptr<GetBooks>(new GetBooks(std::vector<std::shared_ptr<Filter>> ({std::shared_ptr<BookFilter>(new ByBookNameFilter("book1"))})));
    std::shared_ptr<BookSpecification> bspec = std::shared_ptr<BookSpecification>(getBookSpec);

    // act
    bspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedBookTable() == forCheck, true);
}


BOOST_AUTO_TEST_CASE(TestGetBookSpecificationByAuthor){
    // arrange
    BooksObjectMother objectMother;
    std::vector<Book> initial = objectMother.getDefault();
    std::vector<Book> forCheck = objectMother.getWithAuthor(initial, "auth1");

    TestingSession ts;
    ts.initBookTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetBooks> getBookSpec  = std::shared_ptr<GetBooks>(new GetBooks(std::vector<std::shared_ptr<Filter>> ({std::shared_ptr<BookFilter>(new ByAuthorFilter("auth1"))})));
    std::shared_ptr<BookSpecification> bspec = std::shared_ptr<BookSpecification>(getBookSpec);

    // act
    bspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedBookTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestGetBookSpecificationByLibraryID){
    // arrange
    BooksObjectMother objectMother;
    std::vector<Book> initial = objectMother.getDefault();
    std::vector<Book> forCheck = objectMother.getWithLibID(initial, 1);

    TestingSession ts;
    ts.initBookTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetBooks> getBookSpec  = std::shared_ptr<GetBooks>(new GetBooks(std::vector<std::shared_ptr<Filter>> ({std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(1))})));
    std::shared_ptr<BookSpecification> bspec = std::shared_ptr<BookSpecification>(getBookSpec);

    // act
    bspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedBookTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestGetBookSpecificationByID){
    // arrange
    BooksObjectMother objectMother;
    std::vector<Book> initial = objectMother.getDefault();
    std::vector<Book> forCheck = objectMother.getWithID(initial, 1);

    TestingSession ts;
    ts.initBookTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetBooks> getBookSpec  = std::shared_ptr<GetBooks>(new GetBooks(std::vector<std::shared_ptr<Filter>> ({std::shared_ptr<BookFilter>(new ByBookIDFilter(1))})));
    std::shared_ptr<BookSpecification> bspec = std::shared_ptr<BookSpecification>(getBookSpec);

    // act
    bspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedBookTable() == forCheck, true);
}
BOOST_AUTO_TEST_CASE(TestGetBookSpecificationByLogin){
    // arrange
    BooksObjectMother objectMother;
    std::vector<Book> initial = objectMother.getDefault();
    std::vector<Book> forCheck = objectMother.getWithLogin(initial, "user");

    TestingSession ts;
    ts.initBookTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetBooks> getBookSpec  = std::shared_ptr<GetBooks>(new GetBooks(std::vector<std::shared_ptr<Filter>> ({std::shared_ptr<AccountFilter>(new ByLoginFilter("user"))})));
    std::shared_ptr<BookSpecification> bspec = std::shared_ptr<BookSpecification>(getBookSpec);

    // act
    bspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedBookTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestGetBookSpecificationByAuthorLogin){
    // arrange
    BooksObjectMother objectMother;
    std::vector<Book> initial = objectMother.getDefault();
    std::vector<Book> forCheck = objectMother.getWithAuthor(initial, "auth2");
    forCheck = objectMother.getWithLogin(forCheck, "user");

    TestingSession ts;
    ts.initBookTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetBooks> getBookSpec  = std::shared_ptr<GetBooks>(new GetBooks(std::vector<std::shared_ptr<Filter>> (
            {std::shared_ptr<AccountFilter>(new ByLoginFilter("user")),
            std::shared_ptr<BookFilter>(new ByAuthorFilter("auth2"))})));
    std::shared_ptr<BookSpecification> bspec = std::shared_ptr<BookSpecification>(getBookSpec);

    // act
    bspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedBookTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestGetFreeBookSpecificationByName){
    // arrange
    BooksObjectMother objectMother;
    std::vector<Book> initial = objectMother.getDefault();
    std::vector<Book> forCheck = objectMother.getWithLogin(objectMother.getWithName(initial, "book1"), "");

    TestingSession ts;
    ts.initBookTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetFreeBooks> getBookSpec  = std::shared_ptr<GetFreeBooks>(new GetFreeBooks(std::vector<std::shared_ptr<Filter>> ({std::shared_ptr<BookFilter>(new ByBookNameFilter("book1"))})));
    std::shared_ptr<BookSpecification> bspec = std::shared_ptr<BookSpecification>(getBookSpec);

    // act
    bspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedBookTable() == forCheck, true);
}


BOOST_AUTO_TEST_CASE(TestGetFreeBookSpecificationByAuthor){
    // arrange
    BooksObjectMother objectMother;
    std::vector<Book> initial = objectMother.getDefault();
    std::vector<Book> forCheck = objectMother.getWithLogin(objectMother.getWithAuthor(initial, "auth1"), "");

    TestingSession ts;
    ts.initBookTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetFreeBooks> getBookSpec  = std::shared_ptr<GetFreeBooks>(new GetFreeBooks(std::vector<std::shared_ptr<Filter>> ({std::shared_ptr<BookFilter>(new ByAuthorFilter("auth1"))})));
    std::shared_ptr<BookSpecification> bspec = std::shared_ptr<BookSpecification>(getBookSpec);

    // act
    bspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedBookTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestGetFreeBookSpecificationByLibraryID){
    // arrange
    BooksObjectMother objectMother;
    std::vector<Book> initial = objectMother.getDefault();
    std::vector<Book> forCheck = objectMother.getWithLogin(objectMother.getWithLibID(initial, 1), "");

    TestingSession ts;
    ts.initBookTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetFreeBooks> getBookSpec  = std::shared_ptr<GetFreeBooks>(new GetFreeBooks(std::vector<std::shared_ptr<Filter>> ({std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(1))})));
    std::shared_ptr<BookSpecification> bspec = std::shared_ptr<BookSpecification>(getBookSpec);

    // act
    bspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedBookTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestGetFreeBookSpecificationByID){
    // arrange
    BooksObjectMother objectMother;
    std::vector<Book> initial = objectMother.getDefault();
    std::vector<Book> forCheck = objectMother.getWithLogin(objectMother.getWithID(initial, 1), "");

    TestingSession ts;
    ts.initBookTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetFreeBooks> getBookSpec  = std::shared_ptr<GetFreeBooks>(new GetFreeBooks(std::vector<std::shared_ptr<Filter>> ({std::shared_ptr<BookFilter>(new ByBookIDFilter(1))})));
    std::shared_ptr<BookSpecification> bspec = std::shared_ptr<BookSpecification>(getBookSpec);

    // act
    bspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedBookTable() == forCheck, true);
}


BOOST_AUTO_TEST_CASE(TestGetFreeBookSpecificationByAuthorLID){
    // arrange
    BooksObjectMother objectMother;
    std::vector<Book> initial = objectMother.getDefault();
    std::vector<Book> forCheck = objectMother.getWithLogin(objectMother.getWithLibID(objectMother.getWithAuthor(initial, "auth1"), 1), "");

    TestingSession ts;
    ts.initBookTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetFreeBooks> getBookSpec  = std::shared_ptr<GetFreeBooks>(new GetFreeBooks(std::vector<std::shared_ptr<Filter>> (
            {std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(1)),
             std::shared_ptr<BookFilter>(new ByAuthorFilter("auth1"))})));
    std::shared_ptr<BookSpecification> bspec = std::shared_ptr<BookSpecification>(getBookSpec);

    // act
    bspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedBookTable() == forCheck, true);
}



BOOST_AUTO_TEST_CASE(TestBooksQueryClassic){
    // arrange
    BooksObjectMother objectMother;
    std::vector<Book> initial = objectMother.getDefault();
    std::vector<Book> forCheck = objectMother.getWithLogin(objectMother.getWithLibID(objectMother.getWithAuthor(initial, "auth1"), 1), "");

    TestingSession ts;
    ts.initBookTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetFreeBooks> getBookSpec  = std::shared_ptr<GetFreeBooks>(new GetFreeBooks(std::vector<std::shared_ptr<Filter>> (
            {std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(1)),
             std::shared_ptr<BookFilter>(new ByAuthorFilter("auth1"))})));
    std::shared_ptr<BookSpecification> bspec = std::shared_ptr<BookSpecification>(getBookSpec);
    BookRepository repo;
    // act
    repo.query(session, bspec);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedBookTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestBooksQueryLondon){
    // arrange
    BooksObjectMother objectMother;
    std::vector<Book> initial = objectMother.getDefault();
    std::vector<Book> forCheck = objectMother.getWithLogin(objectMother.getWithLibID(objectMother.getWithAuthor(initial, "auth1"), 1), "");

    TestingSession ts;
    ts.initBookTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));

    std::shared_ptr<BookSpecification> bspec = std::shared_ptr<BookSpecification>(new BookSpecificationStub());
    BookRepository repo;
    // act
    repo.query(session, bspec);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedBookTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestBooksAdd){
    // arrange
    BooksObjectMother objectMother;
    std::vector<Book> initial = objectMother.getDefault();
    Book b("book1", "auth1", 3);
    std::vector<Book> forCheck = objectMother.getWithAdd(initial, b);

    TestingSession ts;
    ts.initBookTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));

    BookRepository repo;
    // act
    repo.addBook(session, std::shared_ptr<Book>(new Book("book1", "auth1", 3)));

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedBookTable() == forCheck, true);
}
BOOST_AUTO_TEST_CASE(TestBooksUpd){
    // arrange
    BooksObjectMother objectMother;
    std::vector<Book> initial = objectMother.getDefault();
    Book b("updb1", "upda1", 2);
    std::shared_ptr<Book> book = std::shared_ptr<Book>(new Book("updb1", "upda1", 2));
    book->setID(1);
    std::vector<Book> forCheck = objectMother.getWithUpd(initial, 1, b);

    TestingSession ts;
    ts.initBookTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));

    BookRepository repo;
    // act

    repo.updateBook(session, book);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedBookTable() == forCheck, true);
}
BOOST_AUTO_TEST_CASE(TestBooksDel){
    // arrange
    BooksObjectMother objectMother;
    std::vector<Book> initial = objectMother.getDefault();
    std::vector<Book> forCheck = objectMother.getWithDel(initial, 1);

    TestingSession ts;
    ts.initBookTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    BookRepository repo;
    // act

    repo.removeBook(session, 1);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedBookTable() == forCheck, true);
}
#endif //SRC_TESTBOOKS_H
