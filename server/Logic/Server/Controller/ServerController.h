//
// Created by Екатерина on 18.04.2022.
//

#ifndef SRC_SERVERCONTROLLER_H
#define SRC_SERVERCONTROLLER_H

#include "../DTOs/DTOs.h"
#include <unistd.h>
#include <iostream>

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin codegen
#include "../../../Database/Entities/DBBook/BookFilters/ByAuthorFilter.h"
#include "../../../Database/Entities/DBBook/BookFilters/ByBookNameFilter.h"
#include "../../../Database/DataAccessFacade/Commands/GetBooksCommands/GetFreeBooksCommand.h"
#include "../../../Database/DataAccessFacade/Commands/GetBooksCommands/GetBooksByLoginCommand.h"
#include "../../../Database/DataAccessFacade/Commands/TakeBookCommand/TakeBookCommand.h"
#include "../../../Database/DataAccessFacade/Commands/ReturnBookCommand/ReturnBookCommand.h"
#include "../../../Database/Entities/DBAccount/LibrarianAccount/LibrarianAccountSpecifications/GetLibrarianAccount.h"
#include "../../../Database/DataAccessFacade/Commands/GetAccounts/GetLibrarianAccountCommand.h"
#include "../../../Database/DataAccessFacade/Commands/GetAccounts/GetReaderAccountCommand.h"
#include "../../../Database/DataAccessFacade/Commands/UpdateAccounts/UpdateLibrarianAccountCommand.h"
#include "../../../Database/DataAccessFacade/Commands/UpdateAccounts/UpdateAdminAccountCommand.h"
#include "../../../Database/DataAccessFacade/Commands/UpdateAccounts/UpdateReaderAccountCommand.h"
#include "../../../Database/DataAccessFacade/Commands/GetLibraries/GetlibrariesCommand.h"
#include "../../../Database/DataAccessFacade/Commands/GetLibraries/UpdateLibraries.h"
#include "../../../Database/DataAccessFacade/Commands/GetLibraries/PostLibrariesCommand.h"
#include "../../../Database/DataAccessFacade/Commands/GetBooksCommands/UpdateBookCommand.h"
#include "../../../Database/DataAccessFacade/Commands/GetBooksCommands/DeleteBooksCommand.h"
#include "../../../Database/DataAccessFacade/Commands/GetLibraries/DeleteLibrariesCommand.h"
#include "../../../Database/DataAccessFacade/Commands/DeleteAccounts/DeleteLibrarianAccountCommand.h"
#include "../../../Database/DataAccessFacade/Commands/DeleteAccounts/DeleteAdminAccountCommand.h"
#include "../../../Database/DataAccessFacade/Commands/DeleteAccounts/DeleteReaderAccountCommand.h"

std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}
class ServerController : public oatpp::web::server::api::ApiController {
protected:
    ServerController(const std::shared_ptr<ObjectMapper>& objectMapper)
            : oatpp::web::server::api::ApiController(objectMapper) {}
public:

    static std::shared_ptr<ServerController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>,
                                                                      objectMapper)){
        return std::shared_ptr<ServerController>(new ServerController(objectMapper));
    }

    ENDPOINT_ASYNC("GET", "/api/v1/book", Books ) {

        ENDPOINT_ASYNC_INIT(Books)

        Action act() override {

            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            if (login.empty() || pwd.empty())
                return _return(controller->createResponse(Status::CODE_300));

            std::vector<std::shared_ptr<Book>> books;
            std::vector<std::shared_ptr<Filter>> filters;

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);


            if (queryParams.get("author") != nullptr) {
                std::string s = queryParams.get("author");
                filters.push_back(std::shared_ptr<Filter>(new ByAuthorFilter(replaceAll(s, "+", " "))));
            }
            if (queryParams.get("name") != nullptr)
            {
                std::string s = queryParams.get("name");
                filters.push_back(std::shared_ptr<Filter>(new ByBookNameFilter(replaceAll(s, "+", " "))));
            }
            if (queryParams.get("lib_address") != nullptr) {
                std::string s = queryParams.get("lib_address");
                filters.push_back(std::shared_ptr<Filter>(new ByAddressFilter(replaceAll(s, "+", " "))));
            }
            if (queryParams.get("lib_name") != nullptr) {
                std::string s = queryParams.get("lib_name");
                filters.push_back(std::shared_ptr<Filter>(new ByLibraryNameFilter(replaceAll(s, "+", " "))));
            }
            if (queryParams.get("login") != nullptr) {
                std::string s = queryParams.get("login");
                filters.push_back(std::shared_ptr<Filter>(new ByLoginFilter(replaceAll(s, "+", " "))));
                if (s == login)
                    manager->exec(std::shared_ptr<GetBooksByLoginCommand> (new GetBooksByLoginCommand(books, filters)), login, pwd);

            } else {
                manager->exec(std::shared_ptr<GetFreeBooksCommand> (new GetFreeBooksCommand(books, filters)), login, pwd);

            }

            auto booksDto = BooksDto::createShared();
            oatpp::Vector<oatpp::Object<BookDto>> booksVector ({});

            for (auto &book : books) {
                auto bookDto = BookDto::createShared();
                bookDto->name = book->getName();
                bookDto->author = book->getAuthor();
                bookDto->id = book->getID();
                auto libDto = LibraryDto::createShared();
                libDto->id = book->getLibrary()->getID();
                libDto->address = book->getLibrary()->getAddress();
                libDto->name = book->getLibrary()->getName();
                bookDto->library = libDto;
                booksVector->push_back(bookDto);
            }

            booksDto->books = booksVector;
            /* return Action to start child coroutine to read body */
            return _return(controller->createDtoResponse(Status::CODE_200, booksDto));
        }


    };

    ENDPOINT_ASYNC("PUT", "/api/v1/book/give", BookGiveUpdate ) {

    ENDPOINT_ASYNC_INIT(BookGiveUpdate)

        Action act() override {

            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            if (login.empty() || pwd.empty())
                return _return(controller->createResponse(Status::CODE_300));

            std::vector<std::shared_ptr<Book>> books;

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);

            std::string name, author, login_user;
            if (queryParams.get("author") != nullptr && queryParams.get("name") != nullptr && queryParams.get("login_user") != nullptr) {
                author = replaceAll(queryParams.get("author"), "+", " ");
                name = replaceAll(queryParams.get("name"), "+", " ");
                login_user = replaceAll(queryParams.get("login_user"), "+", " ");
            } else
                return _return(controller->createResponse(Status::CODE_500));

            std::shared_ptr<Book> book = std::shared_ptr<Book>(new Book(name, author));
            try {
                manager->exec(std::shared_ptr<TakeBookCommand>(new TakeBookCommand(login_user, login, book)), login,
                              pwd);
            }
            catch (LogicException)
            {
                return _return(controller->createResponse(Status::CODE_500));
            }

            /* return Action to start child coroutine to read body */
            return _return(controller->createResponse(Status::CODE_200));
        }
    };

    ENDPOINT_ASYNC("PUT", "/api/v1/book/return", BookReturnUpdate ) {

    ENDPOINT_ASYNC_INIT(BookReturnUpdate)

        Action act() override {

            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            if (login.empty() || pwd.empty())
                return _return(controller->createResponse(Status::CODE_300));

            std::vector<std::shared_ptr<Book>> books;

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);

            std::string name, author, login_user;
            if (queryParams.get("author") != nullptr && queryParams.get("name") != nullptr && queryParams.get("login_user") != nullptr) {
                author = replaceAll(queryParams.get("author"), "+", " ");
                name = replaceAll(queryParams.get("name"), "+", " ");
                login_user = replaceAll(queryParams.get("login_user"), "+", " ");
            } else
                return _return(controller->createResponse(Status::CODE_500));

            std::shared_ptr<Book> book = std::shared_ptr<Book>(new Book(name, author));
            try {
                manager->exec(std::shared_ptr<ReturnBookCommand>(new ReturnBookCommand( login_user, login,book)), login,
                              pwd);
            }
            catch (LogicException)
            {
                return _return(controller->createResponse(Status::CODE_500));
            }

            /* return Action to start child coroutine to read body */
            return _return(controller->createResponse(Status::CODE_200));
        }
    };

    ENDPOINT_ASYNC("PUT", "/api/v1/book", BookUpdate ) {

    ENDPOINT_ASYNC_INIT(BookUpdate)
        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<BookDto>>(
                    controller->getDefaultObjectMapper()).callbackTo(&BookUpdate::returnBookResponse);
        }
        Action returnBookResponse( const oatpp::Object<BookDto>& body) {
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            if (login.empty() || pwd.empty())
                return _return(controller->createResponse(Status::CODE_300));

            std::shared_ptr<Library> lib = std::shared_ptr<Library>(new Library(body->library->name,
                                                                                body->library->address));
            lib->setID(body->library->id);
            std::shared_ptr<Book> book = std::shared_ptr<Book>(new Book(body->name,
                                                                        body->author,
                                                                        lib));
            book->setID(body->id);

            manager->exec(std::shared_ptr<Command> (new UpdateBookCommand(book)), login, pwd);

            return _return(controller->createResponse(Status::CODE_200));
        }


    };

    ENDPOINT_ASYNC("POST", "/api/v1/book", BookPoint) {

    ENDPOINT_ASYNC_INIT(BookPoint)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<BookDto>>(controller->getDefaultObjectMapper()).callbackTo(&BookPoint::returnResponse);
        }

        Action returnResponse(const oatpp::Object<BookDto>& body){
            std::string login = request->getQueryParameters().get("login") == nullptr ? "" : request->getQueryParameters().get("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");
            std::vector<std::shared_ptr<Book>> books;
            std::shared_ptr<Library> library = std::shared_ptr<Library>(new Library(body->library->name, body->library->address));
            std::shared_ptr<Book> book = std::shared_ptr<Book>(new Book(body->name, body->author, library));
            books.push_back(book);
            manager->exec(std::shared_ptr<Command>(new AddBooksCommand(books)), login, pwd);
            return _return(controller->createResponse(Status::CODE_200));
        }

    };

    ENDPOINT_ASYNC("DELETE", "/api/v1/book", BookDeletePoint) {

    ENDPOINT_ASYNC_INIT(BookDeletePoint)

        Action act() override {
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);
            int id;
            if (queryParams.get("id") != nullptr) {
                id = atoi(queryParams.get("id")->c_str());
                manager->exec(std::shared_ptr<Command>(new DeleteBooksCommand(id)), login, pwd);
                return _return(controller->createResponse(Status::CODE_200));
            }
            else
                return _return(controller->createResponse(Status::CODE_500));

        }

    };

    ENDPOINT_ASYNC("GET", "/api/v1/login", LoginPoint) {

    ENDPOINT_ASYNC_INIT(LoginPoint)

        Action act() override {
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");
            std::shared_ptr<Account> account;
            try {
                manager->login(login, pwd, account);
            }
            catch (LogicException)
            {
                return _return(controller->createResponse(Status::CODE_500));
            }
            if (account->getRole() == "librarian")
            {
                std::shared_ptr<LibrarianAccount> lacc;
                manager->exec(std::shared_ptr<Command>(new GetLibrarianAccountCommand(lacc, std::vector<std::shared_ptr<AccountFilter>> ({std::shared_ptr<AccountFilter>(new ByAccountIDFilter(account->getID()))}))),
                              login,
                              pwd);
                auto laccDto = LibrarianAccountDTO::createShared();
                auto libDto = LibraryDto::createShared();
                auto accDto = AccountDto::createShared();
                libDto->name = lacc->getLibrary()->getName();
                libDto->address = lacc->getLibrary()->getAddress();
                libDto->id= lacc->getLibrary()->getID();
                accDto->id = lacc->getAccount()->getID();
                accDto->name = lacc->getAccount()->getName();
                accDto->login = lacc->getAccount()->getLogin();
                accDto->password = lacc->getAccount()->getPassword();
                accDto->role = lacc->getAccount()->getRole();
                laccDto->library = libDto;
                laccDto->account = accDto;
                return _return(controller->createDtoResponse(Status::CODE_200, laccDto));
            }
            if (account->getRole() == "reader")
            {
                std::shared_ptr<ReaderAccount> racc;
                manager->exec(std::shared_ptr<Command>(new GetReaderAccountCommand(racc, std::vector<std::shared_ptr<AccountFilter>> ({std::shared_ptr<AccountFilter>(new ByAccountIDFilter(account->getID()))}))),
                              login,
                              pwd);
                auto raccDto = ReaderAccountDTO::createShared();
                auto accDto = AccountDto::createShared();
                accDto->name = racc->getAccount()->getName();
                accDto->id = racc->getAccount()->getID();
                accDto->login = racc->getAccount()->getLogin();
                accDto->password = racc->getAccount()->getPassword();
                accDto->role = racc->getAccount()->getRole();
                raccDto->phone = racc->getPhone();
                raccDto->account = accDto;
                return _return(controller->createDtoResponse(Status::CODE_200, raccDto));

            }
            if (account->getRole() == "admin")
            {
                auto aaccDto = AdminAccountDTO::createShared();
                auto accDto = AccountDto::createShared();
                accDto->name = account->getName();
                accDto->id = account->getID();
                accDto->login = account->getLogin();
                accDto->password = account->getPassword();
                accDto->role = account->getRole();
                aaccDto->account = accDto;
                return _return(controller->createDtoResponse(Status::CODE_200, aaccDto));

            }
            return _return(controller->createResponse(Status::CODE_200));

        }

    };

    ENDPOINT_ASYNC("POST", "/api/v1/registration", RegistrationPoint) {

    ENDPOINT_ASYNC_INIT(RegistrationPoint)

        Action act() override {
            std::string role = request->getQueryParameters().get("role") == nullptr ? "" : request->getQueryParameters().get("role");
            if (role == "admin")
                return request->readBodyToDtoAsync<oatpp::Object<AdminAccountDTO>>(controller->getDefaultObjectMapper()).callbackTo(&RegistrationPoint::returnResponseAdmin);
            if (role == "librarian")
                return request->readBodyToDtoAsync<oatpp::Object<LibrarianAccountDTO>>(controller->getDefaultObjectMapper()).callbackTo(&RegistrationPoint::returnResponseLibrarian);
            if (role == "reader")
                return request->readBodyToDtoAsync<oatpp::Object<ReaderAccountDTO>>(controller->getDefaultObjectMapper()).callbackTo(&RegistrationPoint::returnResponseReader);
            return _return(controller->createResponse(Status::CODE_500));
        }

        Action returnResponseAdmin(const oatpp::Object<AdminAccountDTO>& body){
            try {
                manager->registration(std::shared_ptr<AdminAccount>(new AdminAccount (std::shared_ptr<Account>(new Account(body->account->login,
                                                                                                                       body->account->password,
                                                                                                                       body->account->role,
                                                                                                                       body->account->name)))));
            }
            catch (LogicException)
            {
                return _return(controller->createResponse(Status::CODE_500));
            }
            return _return(controller->createResponse(Status::CODE_200));
        }
        Action returnResponseLibrarian(const oatpp::Object<LibrarianAccountDTO>& body){
            try {
                manager->registration(std::shared_ptr<LibrarianAccount>(new LibrarianAccount (std::shared_ptr<Account>(new Account(body->account->login,
                                                                                                                           body->account->password,
                                                                                                                           body->account->role,
                                                                                                                           body->account->name)),
                                                                                          std::shared_ptr<Library>(new Library(body->library->name,
                                                                                                                               body->library->address)))));
            }
            catch (LogicException)
            {
                return _return(controller->createResponse(Status::CODE_500));
            }
            return _return(controller->createResponse(Status::CODE_200));
        }
        Action returnResponseReader(const oatpp::Object<ReaderAccountDTO>& body){
            try {
                manager->registration(std::shared_ptr<ReaderAccount>(new ReaderAccount (std::shared_ptr<Account>(new Account(body->account->login,
                                                                                                                                   body->account->password,
                                                                                                                                   body->account->role,
                                                                                                                                   body->account->name)),
                                                                                        body->phone)));
            }
            catch (LogicException)
            {
                return _return(controller->createResponse(Status::CODE_500));
            }
            return _return(controller->createResponse(Status::CODE_200));
        }

    };

    ENDPOINT_ASYNC("PUT", "/api/v1/account", UpdateAccountPoint) {

    ENDPOINT_ASYNC_INIT(UpdateAccountPoint)

        Action act() override {
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            std::shared_ptr<Account> account;
            try {
                manager->login(login, pwd, account);
            }
            catch (LogicException)
            {
                return _return(controller->createResponse(Status::CODE_500));
            }
            if (account->getRole() == "librarian")
                return request->readBodyToDtoAsync<oatpp::Object<LibrarianAccountDTO>>(controller->getDefaultObjectMapper()).callbackTo(&UpdateAccountPoint::returnLibrarianResponse);
            if (account->getRole() == "admin")
                return request->readBodyToDtoAsync<oatpp::Object<AdminAccountDTO>>(controller->getDefaultObjectMapper()).callbackTo(&UpdateAccountPoint::returnAdminResponse);
            if (account->getRole() == "reader")
                return request->readBodyToDtoAsync<oatpp::Object<ReaderAccountDTO>>(controller->getDefaultObjectMapper()).callbackTo(&UpdateAccountPoint::returnReaderResponse);

        }
        Action returnLibrarianResponse( const oatpp::Object<LibrarianAccountDTO>& body) {
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");
            std::shared_ptr<Account> account;
            manager->login(login, pwd, account);
            std::shared_ptr<Account> acc = std::shared_ptr<Account>(new Account(body->account->login,
                                                                                body->account->password,
                                                                                body->account->role,
                                                                                body->account->name));
            acc->setID(account->getID());
            std::shared_ptr<Library> lib = std::shared_ptr<Library>(new Library(body->library->name,
                                                                                body->library->address));
            lib->setID(body->library->id);
            std::shared_ptr<LibrarianAccount> lacc = std::shared_ptr<LibrarianAccount>(new LibrarianAccount(acc, lib));
            manager->exec(std::shared_ptr<Command>(new UpdateLibrarianAccountCommand(lacc)), "admin", "admin");
            return _return(controller->createResponse(Status::CODE_200));
        }
        Action returnAdminResponse(const oatpp::Object<AdminAccountDTO>& body) {
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");
            std::shared_ptr<Account> account;
            manager->login(login, pwd, account);
            std::shared_ptr<Account> acc = std::shared_ptr<Account>(new Account(body->account->login,
                                                                                body->account->password,
                                                                                body->account->role,
                                                                                body->account->name));
            acc->setID(account->getID());
            std::shared_ptr<AdminAccount> aacc = std::shared_ptr<AdminAccount>(new AdminAccount(acc));
            manager->exec(std::shared_ptr<Command>(new UpdateAdminAccountCommand(aacc)), "admin", "admin");
            return _return(controller->createResponse(Status::CODE_200));
        }
        Action returnReaderResponse(const oatpp::Object<ReaderAccountDTO>& body) {
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");
            std::shared_ptr<Account> account;
            manager->login(login, pwd, account);
            std::shared_ptr<Account> acc = std::shared_ptr<Account>(new Account(body->account->login,
                                                                                body->account->password,
                                                                                body->account->role,
                                                                                body->account->name));
            acc->setID(account->getID());
            std::shared_ptr<ReaderAccount> racc = std::shared_ptr<ReaderAccount>(new ReaderAccount(acc,
                                                                                                   body->phone));
            manager->exec(std::shared_ptr<Command>(new UpdateReaderAccountCommand(racc)), "admin", "admin");
            return _return(controller->createResponse(Status::CODE_200));
        }

    };

    ENDPOINT_ASYNC("DELETE", "/api/v1/account", DeleteAccountPoint) {

    ENDPOINT_ASYNC_INIT(DeleteAccountPoint)

        Action act() override {
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            std::shared_ptr<Account> account;
            try {
                manager->login(login, pwd, account);
            }
            catch (LogicException)
            {
                return _return(controller->createResponse(Status::CODE_500));
            }

            if (account->getRole() == "librarian")
            {
                manager->exec(std::shared_ptr<Command>(new DeleteLibrarianAccountCommand(account->getID())), "admin", "admin");
                return _return(controller->createResponse(Status::CODE_200));
            }
            if (account->getRole() == "admin")
            {
                manager->exec(std::shared_ptr<Command>(new DeleteAdminAccountCommand(account->getID())), "admin", "admin");
                return _return(controller->createResponse(Status::CODE_200));
            }
            if (account->getRole() == "reader")
            {
                manager->exec(std::shared_ptr<Command>(new DeleteReaderAccountCommand(account->getID())), "admin", "admin");
                return _return(controller->createResponse(Status::CODE_200));
            }
            return _return(controller->createResponse(Status::CODE_500));
        }

    };

    ENDPOINT_ASYNC("GET", "/api/v1/library", LibraryPoint ) {

    ENDPOINT_ASYNC_INIT(LibraryPoint)

        Action act() override {

            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            if (login.empty() || pwd.empty())
                return _return(controller->createResponse(Status::CODE_300));

            std::vector<std::shared_ptr<Library>> libs;
            std::vector<std::shared_ptr<LibraryFilter>> filters;

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);


            if (queryParams.get("address") != nullptr) {
                std::string s = queryParams.get("address");
                filters.push_back(std::shared_ptr<LibraryFilter>(new ByAddressFilter(replaceAll(s, "+", " "))));
            }
            if (queryParams.get("name") != nullptr)
            {
                std::string s = queryParams.get("name");
                filters.push_back(std::shared_ptr<LibraryFilter>(new ByLibraryNameFilter(replaceAll(s, "+", " "))));
            }
            manager->exec(std::shared_ptr<Command> (new GetlibrariesCommand(libs, filters)), login, pwd);

            auto librariesDto = LibrariesDto::createShared();
            oatpp::Vector<oatpp::Object<LibraryDto>> libsVector ({});

            for (auto &lib : libs) {
                auto libDto = LibraryDto::createShared();
                libDto->name = lib->getName();
                libDto->address = lib->getAddress();
                libDto->id = lib->getID();

                libsVector->push_back(libDto);
            }

            librariesDto->libraries = libsVector;
            /* return Action to start child coroutine to read body */
            return _return(controller->createDtoResponse(Status::CODE_200, librariesDto));
        }


    };

    ENDPOINT_ASYNC("PUT", "/api/v1/library", LibraryUpdatePoint ) {

    ENDPOINT_ASYNC_INIT(LibraryUpdatePoint)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<LibraryDto>>(
                    controller->getDefaultObjectMapper()).callbackTo(&LibraryUpdatePoint::returnLibraryResponse);
        }
        Action returnLibraryResponse( const oatpp::Object<LibraryDto>& body) {
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            if (login.empty() || pwd.empty())
                return _return(controller->createResponse(Status::CODE_300));

            std::shared_ptr<Library> lib = std::shared_ptr<Library>(new Library(body->name, body->address));
            lib->setID(body->id);

            manager->exec(std::shared_ptr<Command> (new UpdateLibrariesCommand(lib)), login, pwd);

            return _return(controller->createResponse(Status::CODE_200));
        }


    };

    ENDPOINT_ASYNC("POST", "/api/v1/library", LibraryPostPoint ) {

    ENDPOINT_ASYNC_INIT(LibraryPostPoint)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<LibraryDto>>(
                    controller->getDefaultObjectMapper()).callbackTo(&LibraryPostPoint::returnLibraryResponse);
        }
        Action returnLibraryResponse( const oatpp::Object<LibraryDto>& body) {
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            if (login.empty() || pwd.empty())
                return _return(controller->createResponse(Status::CODE_300));

            std::shared_ptr<Library> lib = std::shared_ptr<Library>(new Library(body->name, body->address));
            lib->setID(body->id);

            manager->exec(std::shared_ptr<Command> (new PostLibrariesCommand(lib)), login, pwd);

            return _return(controller->createResponse(Status::CODE_200));
        }


    };

    ENDPOINT_ASYNC("DELETE", "/api/v1/library", LibraryDeletePoint ) {

    ENDPOINT_ASYNC_INIT(LibraryDeletePoint)

        Action act() override {
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);
            int id;
            if (queryParams.get("id") != nullptr) {
                id = atoi(queryParams.get("id")->c_str());
                manager->exec(std::shared_ptr<Command>(new DeleteLibrariesCommand(id)), login, pwd);
                return _return(controller->createResponse(Status::CODE_200));
            }
            return _return(controller->createResponse(Status::CODE_500));

        }

    };

    /**
     *  Echo body endpoint Coroutine. Mapped to "/body/dto".
     *  Deserialize DTO reveived, and return same DTO
     *  Returns body as MessageDto received in the request
     */

    static std::shared_ptr<DataAccessManager> manager;
};

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- End codegen

#endif //SRC_SERVERCONTROLLER_H
