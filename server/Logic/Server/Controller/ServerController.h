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
#include "../../../Database/DataAccessFacade/Commands/EBookCommands/GetEBooksCommand.h"
#include "../../../Database/DataAccessFacade/Commands/EBookCommands/UpdateEBookCommand.h"
#include "../../../Database/DataAccessFacade/Commands/EBookCommands/DeleteEBookCommand.h"
#include "../../../Database/DataAccessFacade/Commands/EBookCommands/AddEBooksCommand.h"
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

    ENDPOINT_ASYNC("GET", "/api/v1/books", Books) {

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
            if (queryParams.get("login_filter") != nullptr) {
                std::string s = queryParams.get("login_filter");
                filters.push_back(std::shared_ptr<Filter>(new ByLoginFilter(replaceAll(s, "+", " "))));
                if (s == login)
                    manager->exec(std::shared_ptr<GetBooksByLoginCommand> (new GetBooksByLoginCommand(ioc->getBookRepository(), books, filters)), login, pwd);

            } else {
                if (queryParams.get("free") != nullptr) {
                    manager->exec(std::shared_ptr<GetFreeBooksCommand>(
                            new GetFreeBooksCommand(ioc->getBookRepository(), books, filters)), login, pwd);
                }
                else
                {
                    manager->exec(std::shared_ptr<GetBooksByLoginCommand> (new GetBooksByLoginCommand(ioc->getBookRepository(), books, filters)), login, pwd);
                }
            }

            auto booksDto = BooksDto::createShared();
            oatpp::Vector<oatpp::Object<BookDto>> booksVector ({});

            for (auto &book : books) {
                auto bookDto = BookDto::createShared();
                bookDto->name = book->getName();
                bookDto->author = book->getAuthor();
                bookDto->id = book->getID();
                bookDto->lib_id = book->getLibraryID();
                bookDto->login = book->getLogin();
                booksVector->push_back(bookDto);
            }

            booksDto->books = booksVector;
            /* return Action to start child coroutine to read body */
            return _return(controller->createDtoResponse(Status::CODE_200, booksDto));
        }


    };

    ENDPOINT_ASYNC("PATCH", "/api/v1/books/{id}", BookReturnGiveUpdate ) {

    ENDPOINT_ASYNC_INIT(BookReturnGiveUpdate)

        Action act() override {

            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            if (login.empty() || pwd.empty())
                return _return(controller->createResponse(Status::CODE_300));

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);

            std::string login_user;
            std::string action;
            int book_id;
            if (queryParams.get("book_id") != nullptr && queryParams.get("login_user") != nullptr) {
                book_id = std::atoi(replaceAll(queryParams.get("book_id"), "+", " ").c_str());
                login_user = replaceAll(queryParams.get("login_user"), "+", " ");
                action = replaceAll(queryParams.get("action"), "+", " ");
            } else
                return _return(controller->createResponse(Status::CODE_500));

            if (action == "return") {
                try {
                    manager->exec(std::shared_ptr<ReturnBookCommand>(
                            new ReturnBookCommand(ioc->getBookRepository(), login_user, login, book_id)), login,
                                  pwd);
                }
                catch (LogicException) {
                    return _return(controller->createResponse(Status::CODE_500));
                }
            } else if (action == "give")
            {
                try {
                    manager->exec(std::shared_ptr<TakeBookCommand>(
                            new TakeBookCommand(ioc->getBookRepository(), login_user, login, book_id)), login,
                                  pwd);
                }
                catch (LogicException) {
                    return _return(controller->createResponse(Status::CODE_500));
                }
            } else
                return _return(controller->createResponse(Status::CODE_500));

            /* return Action to start child coroutine to read body */
            return _return(controller->createResponse(Status::CODE_200));
        }
    };

    ENDPOINT_ASYNC("PUT", "/api/v1/books/{id}", BookUpdate ) {

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

            std::shared_ptr<Book> book = std::shared_ptr<Book>(new Book(body->name,
                                                                        body->author,
                                                                        body->lib_id));
            book->setID(body->id);

            manager->exec(std::shared_ptr<Command> (new UpdateBookCommand(ioc->getBookRepository(), book)), login, pwd);

            return _return(controller->createResponse(Status::CODE_200));
        }


    };

    ENDPOINT_ASYNC("POST", "/api/v1/books", BookPoint) {

    ENDPOINT_ASYNC_INIT(BookPoint)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<BookDto>>(controller->getDefaultObjectMapper()).callbackTo(&BookPoint::returnResponse);
        }

        Action returnResponse(const oatpp::Object<BookDto>& body){
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");
            std::vector<std::shared_ptr<Book>> books;
            std::shared_ptr<Book> book = std::shared_ptr<Book>(new Book(body->name, body->author, body->lib_id));
            books.push_back(book);
            manager->exec(std::shared_ptr<Command>( new AddBooksCommand(ioc->getBookRepository(), books)), login, pwd);
            return _return(controller->createResponse(Status::CODE_200));
        }

    };

    ENDPOINT_ASYNC("DELETE", "/api/v1/books/{id}", BookDeletePoint) {

    ENDPOINT_ASYNC_INIT(BookDeletePoint)

        Action act() override {
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);
            int id;
            if (queryParams.get("iid") != nullptr) {
                id = atoi(queryParams.get("iid")->c_str());
                manager->exec(std::shared_ptr<Command>(new DeleteBooksCommand(ioc->getBookRepository(), id)), login, pwd);
                return _return(controller->createResponse(Status::CODE_200));
            }
            else
                return _return(controller->createResponse(Status::CODE_500));

        }

    };


    ENDPOINT_ASYNC("GET", "/api/v1/ebooks", EBooks ) {

    ENDPOINT_ASYNC_INIT(EBooks)

        Action act() override {

            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            if (login.empty() || pwd.empty())
                return _return(controller->createResponse(Status::CODE_300));

            std::vector<std::shared_ptr<EBook>> books;
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

            manager->exec(std::shared_ptr<GetEBooksCommand> (new GetEBooksCommand(ioc->getEBookRepository(), books, filters)), login, pwd);


            auto booksDto = EBooksDto::createShared();
            oatpp::Vector<oatpp::Object<EBookDto>> booksVector ({});

            for (auto &book : books) {
                auto bookDto = EBookDto::createShared();
                bookDto->name = book->getName();
                bookDto->author = book->getAuthor();
                bookDto->id = book->getID();
                bookDto->link = book->getLink();
                booksVector->push_back(bookDto);
            }

            booksDto->books = booksVector;
            /* return Action to start child coroutine to read body */
            return _return(controller->createDtoResponse(Status::CODE_200, booksDto));
        }


    };

    ENDPOINT_ASYNC("PUT", "/api/v1/ebooks/{id}", EBookUpdate ) {

    ENDPOINT_ASYNC_INIT(EBookUpdate)
        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<EBookDto>>(
                    controller->getDefaultObjectMapper()).callbackTo(&EBookUpdate::returnBookResponse);
        }
        Action returnBookResponse( const oatpp::Object<EBookDto>& body) {
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            if (login.empty() || pwd.empty())
                return _return(controller->createResponse(Status::CODE_300));

            std::shared_ptr<EBook> book = std::shared_ptr<EBook>(new EBook(body->name,
                                                                        body->author,
                                                                        body->link));
            book->setID(body->id);

            manager->exec(std::shared_ptr<Command> (new UpdateEBookCommand(ioc->getEBookRepository(), book)), login, pwd);

            return _return(controller->createResponse(Status::CODE_200));
        }


    };

    ENDPOINT_ASYNC("POST", "/api/v1/ebooks", EBookPoint) {

    ENDPOINT_ASYNC_INIT(EBookPoint)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<EBookDto>>(controller->getDefaultObjectMapper()).callbackTo(&EBookPoint::returnResponse);
        }

        Action returnResponse(const oatpp::Object<EBookDto>& body){
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");
            std::vector<std::shared_ptr<EBook>> books;
            std::shared_ptr<EBook> book = std::shared_ptr<EBook>(new EBook(body->name, body->author, body->link));
            books.push_back(book);
            manager->exec(std::shared_ptr<Command>( new AddEBooksCommand(ioc->getEBookRepository(), books)), login, pwd);
            return _return(controller->createResponse(Status::CODE_200));
        }

    };

    ENDPOINT_ASYNC("DELETE", "/api/v1/ebooks/{id}", EBookDeletePoint) {

    ENDPOINT_ASYNC_INIT(EBookDeletePoint)

        Action act() override {
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);
            int id;
            if (queryParams.get("iid") != nullptr) {
                id = atoi(queryParams.get("iid")->c_str());
                manager->exec(std::shared_ptr<Command>(new DeleteEBooksCommand(ioc->getEBookRepository(), id)), login, pwd);
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
            auto accDto = AccountDto::createShared();
            accDto->name = account->getName();
            accDto->id = account->getID();
            accDto->login = account->getLogin();
            accDto->password = account->getPassword();
            accDto->role = account->getRole();
            if (account->getRole() == "librarian") {
                std::shared_ptr<LibrarianAccount> lacc;
                manager->exec(std::shared_ptr<Command>(
                        new GetLibrarianAccountCommand(ioc->getLibrarianAccountRepository(), lacc,
                                                       std::vector<std::shared_ptr<AccountFilter>>(
                                                               {std::shared_ptr<AccountFilter>(
                                                                       new ByAccountIDFilter(account->getID()))}))),
                              login,
                              pwd);

                auto laccDto = LibrarianAccountDTO::createShared();
                laccDto->lib_id = lacc->getLibraryID();
                accDto->librarian_acc = laccDto;
            }
            if (account->getRole() == "reader")
            {
                std::shared_ptr<ReaderAccount> racc;
                manager->exec(std::shared_ptr<Command>(new GetReaderAccountCommand(ioc->getReaderAccountRepository(),racc, std::vector<std::shared_ptr<AccountFilter>> ({std::shared_ptr<AccountFilter>(new ByAccountIDFilter(account->getID()))}))),
                              login,
                              pwd);
                auto raccDto = ReaderAccountDTO::createShared();
                raccDto->phone = racc->getPhone();
                accDto->reader_acc = raccDto;
            }
            if (account->getRole() == "admin") {
                auto aaccDto = AdminAccountDTO::createShared();
                accDto->admin_acc = aaccDto;
            }
            return _return(controller->createDtoResponse(Status::CODE_200, accDto));

        }

    };

    ENDPOINT_ASYNC("POST", "/api/v1/registration", RegistrationPoint) {

    ENDPOINT_ASYNC_INIT(RegistrationPoint)

        Action act() override {
//            std::string role = request->getQueryParameters().get("role") == nullptr ? "" : request->getQueryParameters().get("role");
//            if (role == "admin")
//                return request->readBodyToDtoAsync<oatpp::Object<AdminAccountDTO>>(controller->getDefaultObjectMapper()).callbackTo(&RegistrationPoint::returnResponseAdmin);
//            if (role == "librarian")
//                return request->readBodyToDtoAsync<oatpp::Object<LibrarianAccountDTO>>(controller->getDefaultObjectMapper()).callbackTo(&RegistrationPoint::returnResponseLibrarian);
//            if (role == "reader")
//                return request->readBodyToDtoAsync<oatpp::Object<ReaderAccountDTO>>(controller->getDefaultObjectMapper()).callbackTo(&RegistrationPoint::returnResponseReader);
//            return _return(controller->createResponse(Status::CODE_500));
            return request->readBodyToDtoAsync<oatpp::Object<AccountDto>>(
                    controller->getDefaultObjectMapper()).callbackTo(&RegistrationPoint::returnResponse);
        }

        Action returnResponse(const oatpp::Object<AccountDto> &body) {
            if (body->role == "admin") {
                manager->registration(std::shared_ptr<AdminAccount>(
                        new AdminAccount(std::shared_ptr<Account>(new Account(body->login,
                                                                              body->password,
                                                                              body->role,
                                                                              body->name)))));
            }
            if (body->role == "librarian") {
                manager->registration(std::shared_ptr<LibrarianAccount>(
                        new LibrarianAccount(std::shared_ptr<Account>(new Account(body->login,
                                                                              body->password,
                                                                              body->role,
                                                                              body->name)), body->librarian_acc->lib_id)));

            }
            if (body->role == "reader") {
                manager->registration(std::shared_ptr<ReaderAccount>(new ReaderAccount (std::shared_ptr<Account>(new Account(body->login,
                                                                                                                                   body->password,
                                                                                                                                   body->role,
                                                                                                                                   body->name)),
                                                                                             body->reader_acc->phone)));

            }
            return _return(controller->createResponse(Status::CODE_200));
        }

//        Action returnResponseAdmin(const oatpp::Object<AdminAccountDTO>& body){
//            std::string role = request->getQueryParameters().get("role") == nullptr ? "" : request->getQueryParameters().get("role");
//            if (role == "admin")
//                return request->readBodyToDtoAsync<oatpp::Object<AdminAccountDTO>>(controller->getDefaultObjectMapper()).callbackTo(&RegistrationPoint::returnResponseAdmin);
//            if (role == "librarian")
//                return request->readBodyToDtoAsync<oatpp::Object<LibrarianAccountDTO>>(controller->getDefaultObjectMapper()).callbackTo(&RegistrationPoint::returnResponseLibrarian);
//            if (role == "reader")
//                return request->readBodyToDtoAsync<oatpp::Object<ReaderAccountDTO>>(controller->getDefaultObjectMapper()).callbackTo(&RegistrationPoint::returnResponseReader);
//            try {
//                manager->registration(std::shared_ptr<AdminAccount>(new AdminAccount (std::shared_ptr<Account>(new Account(body->account->login,
//                                                                                                                       body->account->password,
//                                                                                                                       body->account->role,
//                                                                                                                       body->account->name)))));
//            }
//            catch (LogicException)
//            {
//                return _return(controller->createResponse(Status::CODE_500));
//            }
//            return _return(controller->createResponse(Status::CODE_200));
//        }
//        Action returnResponseLibrarian(const oatpp::Object<LibrarianAccountDTO>& body){
//            try {
//                manager->registration(std::shared_ptr<LibrarianAccount>(new LibrarianAccount (std::shared_ptr<Account>(new Account(body->account->login,
//                                                                                                                           body->account->password,
//                                                                                                                           body->account->role,
//                                                                                                                           body->account->name)), body->lib_id)));
//            }
//            catch (LogicException)
//            {
//                return _return(controller->createResponse(Status::CODE_500));
//            }
//            return _return(controller->createResponse(Status::CODE_200));
//        }
//        Action returnResponseReader(const oatpp::Object<ReaderAccountDTO>& body){
//            try {
//                manager->registration(std::shared_ptr<ReaderAccount>(new ReaderAccount (std::shared_ptr<Account>(new Account(body->account->login,
//                                                                                                                                   body->account->password,
//                                                                                                                                   body->account->role,
//                                                                                                                                   body->account->name)),
//                                                                                        body->phone)));
//            }
//            catch (LogicException)
//            {
//                return _return(controller->createResponse(Status::CODE_500));
//            }
//            return _return(controller->createResponse(Status::CODE_200));
//        }
//
//    };
    };


    ENDPOINT_ASYNC("GET", "/api/v1/libraries", LibraryPoint ) {

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
            if (queryParams.get("id") != nullptr)
            {
                int id = std::atoi(queryParams.get("id")->c_str());
                filters.push_back(std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(id)));
            }
            manager->exec(std::shared_ptr<Command> (new GetlibrariesCommand(ioc->getLibraryRepository(), libs, filters)), login, pwd);

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

    ENDPOINT_ASYNC("PUT", "/api/v1/libraries/{id}", LibraryUpdatePoint ) {

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

            manager->exec(std::shared_ptr<Command> (new UpdateLibrariesCommand(ioc->getLibraryRepository(), lib)), login, pwd);

            return _return(controller->createResponse(Status::CODE_200));
        }


    };

    ENDPOINT_ASYNC("POST", "/api/v1/libraries", LibraryPostPoint ) {

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

            manager->exec(std::shared_ptr<Command> (new PostLibrariesCommand(ioc->getLibraryRepository(), lib)), login, pwd);

            return _return(controller->createResponse(Status::CODE_200));
        }


    };

    ENDPOINT_ASYNC("DELETE", "/api/v1/libraries/{id}", LibraryDeletePoint ) {

    ENDPOINT_ASYNC_INIT(LibraryDeletePoint)

        Action act() override {
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);
            int id;
            if (queryParams.get("iid") != nullptr) {
                id = atoi(queryParams.get("iid")->c_str());
                manager->exec(std::shared_ptr<Command>(new DeleteLibrariesCommand(ioc->getLibraryRepository(), id)), login, pwd);
                return _return(controller->createResponse(Status::CODE_200));
            }
            return _return(controller->createResponse(Status::CODE_500));

        }

    };

//    ENDPOINT_ASYNC("PUT", "/api/v1/account", UpdateAccountPoint) {
//
//    ENDPOINT_ASYNC_INIT(UpdateAccountPoint)
//
//        Action act() override {
//            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
//            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");
//
//            std::shared_ptr<Account> account;
//            try {
//                manager->login(login, pwd, account);
//            }
//            catch (LogicException)
//            {
//                return _return(controller->createResponse(Status::CODE_500));
//            }
//            if (account->getRole() == "librarian")
//                return request->readBodyToDtoAsync<oatpp::Object<LibrarianAccountDTO>>(controller->getDefaultObjectMapper()).callbackTo(&UpdateAccountPoint::returnLibrarianResponse);
//            if (account->getRole() == "admin")
//                return request->readBodyToDtoAsync<oatpp::Object<AdminAccountDTO>>(controller->getDefaultObjectMapper()).callbackTo(&UpdateAccountPoint::returnAdminResponse);
//            if (account->getRole() == "reader")
//                return request->readBodyToDtoAsync<oatpp::Object<ReaderAccountDTO>>(controller->getDefaultObjectMapper()).callbackTo(&UpdateAccountPoint::returnReaderResponse);
//
//        }
//        Action returnLibrarianResponse( const oatpp::Object<LibrarianAccountDTO>& body) {
//            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
//            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");
//            std::shared_ptr<Account> account;
//            manager->login(login, pwd, account);
//            std::shared_ptr<Account> acc = std::shared_ptr<Account>(new Account(body->account->login,
//                                                                                body->account->password,
//                                                                                body->account->role,
//                                                                                body->account->name));
//            std::shared_ptr<LibrarianAccount> lacc = std::shared_ptr<LibrarianAccount>(new LibrarianAccount(acc, body->lib_id));
//            manager->exec(std::shared_ptr<Command>(new UpdateLibrarianAccountCommand(ioc->getLibrarianAccountRepository(), lacc)), "admin", "admin");
//            return _return(controller->createResponse(Status::CODE_200));
//        }
//        Action returnAdminResponse(const oatpp::Object<AdminAccountDTO>& body) {
//            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
//            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");
//            std::shared_ptr<Account> account;
//            manager->login(login, pwd, account);
//            std::shared_ptr<Account> acc = std::shared_ptr<Account>(new Account(body->account->login,
//                                                                                body->account->password,
//                                                                                body->account->role,
//                                                                                body->account->name));
//            acc->setID(account->getID());
//            std::shared_ptr<AdminAccount> aacc = std::shared_ptr<AdminAccount>(new AdminAccount(acc));
//            manager->exec(std::shared_ptr<Command>(new UpdateAdminAccountCommand(ioc->getAdminAccountRepository(), aacc)), "admin", "admin");
//            return _return(controller->createResponse(Status::CODE_200));
//        }
//        Action returnReaderResponse(const oatpp::Object<ReaderAccountDTO>& body) {
//            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
//            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");
//            std::shared_ptr<Account> account;
//            manager->login(login, pwd, account);
//            std::shared_ptr<Account> acc = std::shared_ptr<Account>(new Account(body->account->login,
//                                                                                body->account->password,
//                                                                                body->account->role,
//                                                                                body->account->name));
//            acc->setID(account->getID());
//            std::shared_ptr<ReaderAccount> racc = std::shared_ptr<ReaderAccount>(new ReaderAccount(acc,
//                                                                                                   body->phone));
//            manager->exec(std::shared_ptr<Command>(new UpdateReaderAccountCommand(ioc->getReaderAccountRepository(), racc)), "admin", "admin");
//            return _return(controller->createResponse(Status::CODE_200));
//        }
//
//    };
//
//    ENDPOINT_ASYNC("DELETE", "/api/v1/account", DeleteAccountPoint) {
//
//    ENDPOINT_ASYNC_INIT(DeleteAccountPoint)
//
//        Action act() override {
//            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
//            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");
//
//            std::shared_ptr<Account> account;
//            try {
//                manager->login(login, pwd, account);
//            }
//            catch (LogicException)
//            {
//                return _return(controller->createResponse(Status::CODE_500));
//            }
//
//            if (account->getRole() == "librarian")
//            {
//                manager->exec(std::shared_ptr<Command>(new DeleteLibrarianAccountCommand(ioc->getLibrarianAccountRepository(),account->getID())), "admin", "admin");
//                return _return(controller->createResponse(Status::CODE_200));
//            }
//            if (account->getRole() == "admin")
//            {
//                manager->exec(std::shared_ptr<Command>(new DeleteAdminAccountCommand(ioc->getAdminAccountRepository(), account->getID())), "admin", "admin");
//                return _return(controller->createResponse(Status::CODE_200));
//            }
//            if (account->getRole() == "reader")
//            {
//                manager->exec(std::shared_ptr<Command>(new DeleteReaderAccountCommand(ioc->getReaderAccountRepository(), account->getID())), "admin", "admin");
//                return _return(controller->createResponse(Status::CODE_200));
//            }
//            return _return(controller->createResponse(Status::CODE_500));
//        }
//
//    };
    /**
     *  Echo body endpoint Coroutine. Mapped to "/body/dto".
     *  Deserialize DTO reveived, and return same DTO
     *  Returns body as MessageDto received in the request
     */

    static std::shared_ptr<DataAccessManager> manager;
    static std::shared_ptr<IIocRepository> ioc;
};

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- End codegen

#endif //SRC_SERVERCONTROLLER_H
