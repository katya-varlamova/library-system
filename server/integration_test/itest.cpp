//
// Created by Екатерина on 30.11.2022.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file
#define BOOST_TEST_MODULE test_module

#include <boost/test/included/unit_test.hpp>
#include <SqlIoc/IocRepository.h>
#include <SqlIoc/SqlIoc.h>
#include <DataAccessFacade/DataAccessFacade.h>
#include <DataAccessFacade/Commands/BookCommands/GetFreeBooksCommand.h>
#include <DataAccessFacade/Commands/BookCommands/GetBooksByLoginCommand.h>
#include <DataAccessFacade/Commands/BookCommands/AddBooksCommand.h>
#include <Entities/DBBook/BookFilters/ByBookNameFilter.h>
#include <DataAccessFacade/Commands/BookCommands/UpdateBookCommand.h>
#include <Entities/DBBook/BookFilters/ByBookIDFilter.h>
#include <DataAccessFacade/Commands/BookCommands/DeleteBooksCommand.h>
#include <DataAccessFacade/Commands/AccountCommands/RegisterCommand/RegisterAdminCommand.h>
#include <DataAccessFacade/Commands/AccountCommands/DeleteAccounts/DeleteAdminAccountCommand.h>
#include <DataAccessFacade/Commands/AccountCommands/RegisterCommand/RegisterReaderCommand.h>
#include <DataAccessFacade/Commands/AccountCommands/RegisterCommand/RegisterLibrarianCommand.h>
#include <DataAccessFacade/Commands/AccountCommands/DeleteAccounts/DeleteReaderAccountCommand.h>
#include <DataAccessFacade/Commands/AccountCommands/DeleteAccounts/DeleteLibrarianAccountCommand.h>
#include "DataAccessFacade/Commands/LibraryCommands/DeleteLibrariesCommand.h"
#include "DataAccessFacade/Commands/LibraryCommands/PostLibrariesCommand.h"
#include "DataAccessFacade/Commands/LibraryCommands/UpdateLibraries.h"
#include "DataAccessFacade/Commands/LibraryCommands/GetlibrariesCommand.h"
#include "Entities/DBLibrary/LibraryRepository.h"
#include "../Logic/Configuration/Configuration.h"
#include "../Logic/Configuration/FileConfiguration.h"

std::shared_ptr<IIocRepository> preapre()
{
    std::shared_ptr<Configuration> configuration = std::shared_ptr<Configuration>(new FileConfiguration("itest_config.json"));
    configuration->read();
    std::shared_ptr<IIocRepository> ioc = std::shared_ptr<IIocRepository>(new SqlIocRepositories(configuration));
    return ioc;
}
BOOST_AUTO_TEST_CASE(TestLibrariesIntegration){
    // arrange
    auto ioc = preapre();
    std::vector<std::shared_ptr<Library>> libs;

    std::vector<std::shared_ptr<LibraryFilter>> filters;
    GetlibrariesCommand getAllCommand = GetlibrariesCommand(ioc->getLibraryRepository(),libs, filters);

    filters = {std::shared_ptr<LibraryFilter>(new ByLibraryNameFilter("cordova public library"))};
    GetlibrariesCommand getByNameCommand = GetlibrariesCommand(ioc->getLibraryRepository(),libs, filters);

    filters = {std::shared_ptr<LibraryFilter>(new ByAddressFilter("101 first street"))};
    GetlibrariesCommand getByAddressCommand = GetlibrariesCommand(ioc->getLibraryRepository(),libs, filters);

    filters = {std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(1))};
    GetlibrariesCommand getByIDCommand = GetlibrariesCommand(ioc->getLibraryRepository(),libs, filters);

    auto l = std::shared_ptr<Library>(new Library("newLib", "newAddress"));
    PostLibrariesCommand postLibrariesCommand = PostLibrariesCommand(ioc->getLibraryRepository(), l);

    filters = {std::shared_ptr<LibraryFilter>(new ByLibraryNameFilter("newLib")),
               std::shared_ptr<LibraryFilter>(new ByAddressFilter("newAddress"))};
    GetlibrariesCommand getNewCommand = GetlibrariesCommand(ioc->getLibraryRepository(),libs, filters);

    DataAccessFacade facade = DataAccessFacade(ioc->getConnectionPool());
    auto updlib = std::shared_ptr<Library>(new Library("updatedn", "updateda"));
    facade.connectDB();

    // act
    facade.execute(getAllCommand, "reader");
    // assert
    BOOST_CHECK_EQUAL(libs.size() == 10, true);

    // act
    facade.execute(getByNameCommand, "reader");
    // assert
    BOOST_CHECK_EQUAL(libs.size() == 1, true);

    // act
    facade.execute(getByAddressCommand, "reader");
    // assert
    BOOST_CHECK_EQUAL(libs.size() == 1, true);

    // act
    facade.execute(getByIDCommand, "reader");
    // assert
    BOOST_CHECK_EQUAL(libs.size() == 1, true);

    // act
    facade.execute(postLibrariesCommand, "admin");
    facade.execute(getAllCommand, "reader");
    // assert
    BOOST_CHECK_EQUAL(libs.size() == 11, true);

    // arrange
    facade.execute(getNewCommand, "reader");
    updlib->setID(libs[0]->getID());
    UpdateLibrariesCommand updateLibrariesCommand = UpdateLibrariesCommand(ioc->getLibraryRepository(), updlib);
    filters = {std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(libs[0]->getID()))};
    GetlibrariesCommand getByNewIDCommand = GetlibrariesCommand(ioc->getLibraryRepository(),libs, filters);

    //act
    facade.execute(updateLibrariesCommand, "admin");
    facade.execute(getByNewIDCommand, "reader");
    // assert
    BOOST_CHECK_EQUAL(libs[0]->getName() == "updatedn" && libs[0]->getAddress() == "updateda", true);


    // arrange
    DeleteLibrariesCommand deleteLibrariesCommand = DeleteLibrariesCommand(ioc->getLibraryRepository(), updlib->getID());
    // act

    facade.execute(deleteLibrariesCommand, "admin");
    facade.execute(getAllCommand, "reader");

    // assert
    BOOST_CHECK_EQUAL(libs.size() == 10, true);

    facade.disconnectDB();
}

BOOST_AUTO_TEST_CASE(TestBooksIntegration){
    // arrange
    auto ioc = preapre();

    std::shared_ptr<IBookRepository> repository = std::shared_ptr<IBookRepository> (ioc->getBookRepository());
    std::vector<std::shared_ptr<Book>> books;

    std::vector<std::shared_ptr<Filter>> filters;
    GetFreeBooksCommand getFreeBooksCommand = GetFreeBooksCommand(repository, books, filters);
    GetBooksByLoginCommand getAllBooksCommand = GetBooksByLoginCommand(ioc->getBookRepository(),books, filters);

    filters = {std::shared_ptr<Filter>(new ByBookNameFilter("harry potter collection (harry potter  #1-6)"))};
    GetBooksByLoginCommand getBooksByNameCommand = GetBooksByLoginCommand(repository, books, filters);

    filters = {std::shared_ptr<Filter>(new ByAuthorFilter("douglas adams"))};
    GetBooksByLoginCommand getBooksByAuthorCommand = GetBooksByLoginCommand(repository, books, filters);

    filters = {std::shared_ptr<Filter>(new ByLibraryNameFilter("cordova public library"))};
    GetBooksByLoginCommand getBooksByLibNameCommand = GetBooksByLoginCommand(repository, books, filters);

    filters = {std::shared_ptr<Filter>(new ByAddressFilter("101 first street"))};
    GetBooksByLoginCommand getBooksByAddressCommand = GetBooksByLoginCommand(repository, books, filters);


    std::shared_ptr<ILibraryRepository> libRepository = std::shared_ptr<ILibraryRepository> (ioc->getLibraryRepository());

    books = {std::shared_ptr<Book> (new Book("name", "author", 1))};

    AddBooksCommand addBooksCommand = AddBooksCommand(repository, libRepository, books);

    filters = {std::shared_ptr<Filter>(new ByBookNameFilter("name")),
               std::shared_ptr<Filter>(new ByAuthorFilter("author"))
    };
    GetBooksByLoginCommand getNewBookCommand = GetBooksByLoginCommand(ioc->getBookRepository(),books, filters);

    auto updbook = std::shared_ptr<Book>(new Book("updatedn", "updateda", 1));

    DataAccessFacade facade = DataAccessFacade(ioc->getConnectionPool());
    facade.connectDB();

    // act
    facade.execute(getAllBooksCommand);
    //assert
    BOOST_CHECK_EQUAL(books.size() == 10, true);

    // act
    facade.execute(getFreeBooksCommand);
    //assert
    BOOST_CHECK_EQUAL(books.size() == 6, true);

    // act
    facade.execute(getBooksByNameCommand);
    //assert
    BOOST_CHECK_EQUAL(books.size() == 2, true);

    // act
    facade.execute(getBooksByAuthorCommand);
    //assert
    BOOST_CHECK_EQUAL(books.size() == 1, true);

    // act
    facade.execute(getBooksByAddressCommand);
    //assert
    BOOST_CHECK_EQUAL(books.size() == 5, true);

    // act
    facade.execute(getBooksByLibNameCommand);
    //assert
    BOOST_CHECK_EQUAL(books.size() == 0, true);

    // act
    facade.execute(addBooksCommand);
    facade.execute(getAllBooksCommand);
    //assert
    BOOST_CHECK_EQUAL(books.size() == 11, true);

    // act
    facade.execute(getNewBookCommand);
    //assert
    BOOST_CHECK_EQUAL(books.size() == 1, true);

    // arrange
    updbook->setID(books[0]->getID());
    UpdateBookCommand updateBookCommand = UpdateBookCommand(ioc->getBookRepository(), ioc->getLibraryRepository(), updbook);
    filters = {std::shared_ptr<Filter>(new ByBookIDFilter(books[0]->getID()))};
    GetBooksByLoginCommand getByNewIDCommand = GetBooksByLoginCommand(ioc->getBookRepository(), books, filters);

    //act
    facade.execute(updateBookCommand, "admin");
    facade.execute(getByNewIDCommand, "reader");

    // assert
    BOOST_CHECK_EQUAL(books[0]->getName() == "updatedn" && books[0]->getAuthor()== "updateda", true);

    // arrange
    DeleteBooksCommand deleteBooksCommand = DeleteBooksCommand(ioc->getBookRepository(), updbook->getID());
    // act

    facade.execute(deleteBooksCommand, "admin");
    facade.execute(getAllBooksCommand, "reader");

    // assert
    BOOST_CHECK_EQUAL(books.size() == 10, true);


    facade.disconnectDB();

}
BOOST_AUTO_TEST_CASE(TestAuthIntegration){
    // arrange
    auto ioc = preapre();
    std::shared_ptr<IAccountRepository> repository = std::shared_ptr<IAccountRepository> (ioc->getAccountRepository());
    std::vector<std::shared_ptr<Account>> acc;
    AuthCommand command = AuthCommand(repository, "hashley@bailey-phillips.info", acc);
    DataAccessFacade facade = DataAccessFacade(ioc->getConnectionPool());
    facade.connectDB();
    // act
    facade.execute(command);
    // assert
    BOOST_CHECK_EQUAL(acc.size() == 1 && acc[0]->getPassword() == "SL_90EXmH#", true);
    facade.disconnectDB();
}

BOOST_AUTO_TEST_CASE(TestRegistrationIntegration){
    // arrange
    auto ioc = preapre();

    std::shared_ptr<Account> acc(new Account("login", "pass", "reader", "name"));
    std::shared_ptr<AdminAccount> aacc(new AdminAccount(acc));
    std::shared_ptr<ReaderAccount> racc(new ReaderAccount(acc, "123"));
    std::shared_ptr<LibrarianAccount> lacc(new LibrarianAccount(acc, 1));
    RegisterAdminCommand registerAdminCommand = RegisterAdminCommand(ioc->getAdminAccountRepository(), aacc);
    RegisterReaderCommand registerReaderCommand = RegisterReaderCommand(ioc->getReaderAccountRepository(), racc);
    RegisterLibrarianCommand registerLibrarianCommand = RegisterLibrarianCommand(ioc->getLibrarianAccountRepository(), lacc);

    std::vector<std::shared_ptr<Account>> authacc;
    AuthCommand authCommand = AuthCommand(ioc->getAccountRepository(), "login", authacc);

    DataAccessFacade facade = DataAccessFacade(ioc->getConnectionPool());
    facade.connectDB();

    // act
    facade.execute(registerAdminCommand);
    facade.execute(authCommand);
    // assert
    BOOST_CHECK_EQUAL(authacc[0]->getPassword() == acc->getPassword(), true);
    DeleteAdminAccountCommand deleteAdminAccountCommand = DeleteAdminAccountCommand(ioc->getAdminAccountRepository(), ioc->getAccountRepository(), authacc[0]->getID());
    facade.execute(deleteAdminAccountCommand);

    // act
    facade.execute(registerReaderCommand);
    facade.execute(authCommand);
    // assert
    BOOST_CHECK_EQUAL(authacc[0]->getPassword() == acc->getPassword(), true);
    DeleteReaderAccountCommand deleteReaderAccountCommand = DeleteReaderAccountCommand(ioc->getReaderAccountRepository(), ioc->getAccountRepository(), authacc[0]->getID());
    facade.execute(deleteReaderAccountCommand);

    // act
    facade.execute(registerLibrarianCommand);
    facade.execute(authCommand);
    // assert
    BOOST_CHECK_EQUAL(authacc[0]->getPassword() == acc->getPassword(), true);
    DeleteLibrarianAccountCommand deleteLibrarianAccountCommand = DeleteLibrarianAccountCommand(ioc->getLibrarianAccountRepository(), ioc->getAccountRepository(), authacc[0]->getID());
    facade.execute(deleteLibrarianAccountCommand);

    facade.disconnectDB();
}