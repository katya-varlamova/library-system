//
// Created by Екатерина on 18.04.2022.
//

#ifndef SRC_SERVERCONTROLLERRESTAPI_H
#define SRC_SERVERCONTROLLERRESTAPI_H

#include "../DTOs/DTOsRestApi.h"
#include <unistd.h>
#include <iostream>

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/utils/String.hpp"
#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin codegen
#include "../../../Database/Entities/DBBook/BookFilters/ByAuthorFilter.h"
#include "../../../Database/Entities/DBBook/BookFilters/ByBookNameFilter.h"
#include "DataAccessFacade/Commands/BookCommands/GetFreeBooksCommand.h"
#include "DataAccessFacade/Commands/BookCommands/GetBooksByLoginCommand.h"
#include "../../../Database/DataAccessFacade/Commands/BookCommands/TakeBookCommand/TakeBookCommand.h"
#include "../../../Database/DataAccessFacade/Commands/BookCommands/ReturnBookCommand/ReturnBookCommand.h"
#include "DataAccessFacade/Commands/AccountCommands/GetLibrarianAccountCommand.h"
#include "DataAccessFacade/Commands/AccountCommands/GetReaderAccountCommand.h"
#include "../../../Database/DataAccessFacade/Commands/AccountCommands/UpdateAccounts/UpdateLibrarianAccountCommand.h"
#include "../../../Database/DataAccessFacade/Commands/AccountCommands/UpdateAccounts/UpdateAdminAccountCommand.h"
#include "../../../Database/DataAccessFacade/Commands/AccountCommands/UpdateAccounts/UpdateReaderAccountCommand.h"
#include "DataAccessFacade/Commands/LibraryCommands/GetlibrariesCommand.h"
#include "DataAccessFacade/Commands/LibraryCommands/UpdateLibraries.h"
#include "DataAccessFacade/Commands/LibraryCommands/PostLibrariesCommand.h"
#include "DataAccessFacade/Commands/BookCommands/UpdateBookCommand.h"
#include "DataAccessFacade/Commands/BookCommands/DeleteBooksCommand.h"
#include "DataAccessFacade/Commands/LibraryCommands/DeleteLibrariesCommand.h"
#include "../../../Database/DataAccessFacade/Commands/AccountCommands/DeleteAccounts/DeleteLibrarianAccountCommand.h"
#include "../../../Database/DataAccessFacade/Commands/AccountCommands/DeleteAccounts/DeleteAdminAccountCommand.h"
#include "../../../Database/DataAccessFacade/Commands/AccountCommands/DeleteAccounts/DeleteReaderAccountCommand.h"
#include "../../../Database/DataAccessFacade/Commands/unused/EBookCommands/GetEBooksCommand.h"
#include "../../../Database/DataAccessFacade/Commands/unused/EBookCommands/UpdateEBookCommand.h"
#include "../../../Database/DataAccessFacade/Commands/unused/EBookCommands/DeleteEBookCommand.h"
#include "../../../Database/DataAccessFacade/Commands/unused/EBookCommands/AddEBooksCommand.h"
#include "JWTAuth.h"
#include "../../DataAccessManager/DataAccessManagerRest.h"

std::string replaceAll(std::string str, const std::vector<std::string>& froms, const std::vector<std::string>& tos) {
    for (int i = 0; i < froms.size(); i++) {
        size_t start_pos = 0;
        while ((start_pos = str.find(froms[i], start_pos)) != std::string::npos) {
            str.replace(start_pos, froms[i].length(), tos[i]);
            start_pos += tos[i].length();
        }
    }
    return str;
}
class ServerControllerRestApi : public oatpp::web::server::api::ApiController {
protected:
    ServerControllerRestApi(const std::shared_ptr<ObjectMapper>& objectMapper)
            : oatpp::web::server::api::ApiController(objectMapper) {}
public:

    static std::shared_ptr<ServerControllerRestApi> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>,
                                                                      objectMapper)){
        return std::shared_ptr<ServerControllerRestApi>(new ServerControllerRestApi(objectMapper));
    }
    ENDPOINT_INFO(Books){
        info->summary = "information about books (all filters applied in AND strategy)";

        info->headers.add<oatpp::String>("token");
        info->headers["token"].required = true;
        info->headers["token"].addExample("1", oatpp::String("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.ey"));

        info->queryParams.add<oatpp::String>("author").required = false;
        info->queryParams["author"].description = "author of books to be returned";
        info->queryParams["author"].addExample("1", oatpp::String("Lev Tolstoy"));

        info->queryParams.add<oatpp::String>("name").required = false;
        info->queryParams["name"].description = "name of books to be returned";
        info->queryParams["name"].addExample("1", oatpp::String("Voina i mir"));

        info->queryParams.add<oatpp::Int64>("lib_id").required = false;
        info->queryParams["lib_id"].description = "identifier of the Library returned from GET Library request; describing library of the books to be returned";
        info->queryParams["lib_id"].addExample("1", oatpp::String("22"));

        info->queryParams.add<oatpp::String>("login_filter").required = false;
        info->queryParams["login_filter"].description = "must be the same with the login from header";
        info->queryParams["login_filter"].addExample("1", oatpp::String("katya_varlamova"));

        info->queryParams.add<oatpp::String>("free").required = false;
        info->queryParams["free"].description = "can have any value; if this param exists, only free books are returned";
        info->queryParams["free"].addExample("1", oatpp::String("yes"));

        info->addResponse(Status::CODE_400).description = "in case if the login from header not the same with login_filter or in case of parsing error";;
        info->addResponse(Status::CODE_401).description = "auth failed or no such user or credentials are not given";
        info->addResponse(Status::CODE_500).description = "internal error";
        info->addResponse<Object<BooksDto>>(Status::CODE_200, "application/json");
    };

    ENDPOINT_ASYNC("GET", "/api/v2/books", Books) {

        ENDPOINT_ASYNC_INIT(Books)

        Action act() override {

            std::string token = request->getHeader("token") == nullptr ? "" : request->getHeader("token");
            JWTAuth auth;
            if (!auth.checkToken(token))
                return _return(controller->createResponse(Status::CODE_401));

            std::string role = auth.getRole(token);
            std::string login = auth.getLogin(token);

            std::vector<std::shared_ptr<Book>> books;
            std::vector<std::shared_ptr<Filter>> filters;

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);


            if (queryParams.get("author") != nullptr) {
                std::string s = queryParams.get("author");
                filters.push_back(std::shared_ptr<Filter>(new ByAuthorFilter(replaceAll(s, {"+"}, {" "}))));
            }
            if (queryParams.get("name") != nullptr)
            {
                std::string s = queryParams.get("name");
                filters.push_back(std::shared_ptr<Filter>(new ByBookNameFilter(replaceAll(s, {"+", "%23","%40"}, {" ","#","@"}) )));
            }
            if (queryParams.get("lib_id") != nullptr) {
                int lib_id = std::atoi(replaceAll(queryParams.get("lib_id"), {"+", "%23","%40"}, {" ","#","@"}).c_str());
                filters.push_back(std::shared_ptr<Filter>(new ByLibraryIDFilter(lib_id)));
            }
            if (queryParams.get("login_filter") != nullptr) {
                std::string s = queryParams.get("login_filter");
                s = replaceAll(s, {"+", "%23","%40"}, {" ","#","@"} );
                filters.push_back(std::shared_ptr<Filter>(new ByLoginFilter(s)));
                if (s == login) {
                    try {
                        manager->exec(std::shared_ptr<GetBooksByLoginCommand>(
                                new GetBooksByLoginCommand(ioc->getBookRepository(), books, filters)), role);
                    }
                    catch (LogicException) {
                        return _return(controller->createResponse(Status::CODE_400));
                    }
                } else
                {
                    return _return(controller->createResponse(Status::CODE_500));
                }

            } else {
                if (queryParams.get("free") != nullptr) {
                    try {
                        manager->exec(std::shared_ptr<GetFreeBooksCommand>(
                                new GetFreeBooksCommand(ioc->getBookRepository(), books, filters)), role);
                    }
                    catch (LogicException) {
                        return _return(controller->createResponse(Status::CODE_500));
                    }
                }
                else
                {
                    try {
                        manager->exec(std::shared_ptr<GetBooksByLoginCommand>(
                                new GetBooksByLoginCommand(ioc->getBookRepository(), books, filters)), role);
                    }
                    catch (LogicException) {
                        return _return(controller->createResponse(Status::CODE_500));
                    }
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


    ENDPOINT_INFO(BookReturnGiveUpdate){
        info->summary = "makes book available or in use; call succeeds only if user is librarian";

        info->headers.add<oatpp::String>("token");
        info->headers["token"].required = true;
        info->headers["token"].addExample("1", oatpp::String("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.ey"));

        info->pathParams.add<oatpp::Int64>("id").required = true;
        info->pathParams["id"].description = "identifier of the Book returned from GET Book request;";
        info->pathParams["id"].addExample("1", oatpp::String("23"));

        info->queryParams.add<oatpp::String>("login_user").required = true;
        info->queryParams["login_user"].description = "login of reader";
        info->queryParams["login_user"].addExample("1", oatpp::String("katya_varlamova"));

        info->queryParams.add<oatpp::String>("action").required = true;
        info->queryParams["action"].description = "give: in case of making book in use, return: otherwise";
        info->queryParams["action"].addExample("1", oatpp::String("give"));

        info->addResponse(Status::CODE_400).description = "required parameters are not given";;
        info->addResponse(Status::CODE_401).description = "auth failed or no such user or credentials are not given";
        info->addResponse(Status::CODE_403).description = "role doesn't allow such actions";
        info->addResponse(Status::CODE_500).description = "internal error";
    };

    ENDPOINT_ASYNC("PATCH", "/api/v2/books/{id}", BookReturnGiveUpdate ) {

    ENDPOINT_ASYNC_INIT(BookReturnGiveUpdate)

        Action act() override {

            std::string token = request->getHeader("token") == nullptr ? "" : request->getHeader("token");
            JWTAuth auth;
            if (!auth.checkToken(token))
                return _return(controller->createResponse(Status::CODE_401));

            std::string role = auth.getRole(token);
            std::string login = auth.getLogin(token);
            if (role != "librarian")
                return _return(controller->createResponse(Status::CODE_403));

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);

            std::string login_user;
            std::string action;
            int book_id;
            if (request->getPathVariable("id") != nullptr && queryParams.get("login_user") != nullptr) {
                book_id = atoi(request->getPathVariable("id")->c_str());
                login_user = replaceAll(queryParams.get("login_user"), {"+", "%23","%40"}, {" ","#","@"}) ;
                action = replaceAll(queryParams.get("action"), {"+", "%23","%40"}, {" ","#","@"}) ;
            } else
                return _return(controller->createResponse(Status::CODE_400));

            if (action == "return") {
                try {
                    manager->exec(std::shared_ptr<ReturnBookCommand>(
                            new ReturnBookCommand(ioc->getAccountRepository(), ioc->getBookRepository(), login_user, login, book_id)), role);
                }
                catch (LogicException) {
                    return _return(controller->createResponse(Status::CODE_500));
                }
            } else if (action == "give")
            {
                try {
                    manager->exec(std::shared_ptr<TakeBookCommand>(
                            new TakeBookCommand(ioc->getAccountRepository(), ioc->getBookRepository(), login_user, login, book_id)), role);
                }
                catch (LogicException) {
                    return _return(controller->createResponse(Status::CODE_500));
                }
            } else
                return _return(controller->createResponse(Status::CODE_400));

            /* return Action to start child coroutine to read body */
            return _return(controller->createResponse(Status::CODE_200));
        }
    };


    ENDPOINT_INFO(BookUpdate){
        info->summary = "update book with given identifier; call succeeds only if user is admin";

        info->headers.add<oatpp::String>("token");
        info->headers["token"].required = true;
        info->headers["token"].addExample("1", oatpp::String("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.ey"));

        info->pathParams.add<oatpp::Int64>("id").required = true;
        info->pathParams["id"].description = "identifier of the Book returned from GET Book request;";
        info->pathParams["id"].addExample("1", oatpp::String("23"));

        info->addConsumes<Object<BookDto>>("application/json");

        info->addResponse(Status::CODE_401).description = "auth failed or no such user or credentials are not given";
        info->addResponse(Status::CODE_403).description = "role doesn't allow such actions";
        info->addResponse(Status::CODE_500).description = "internal error";
        info->addResponse(Status::CODE_200).description = "update succeeded";
    };

    ENDPOINT_ASYNC("PUT", "/api/v2/books/{id}", BookUpdate ) {

    ENDPOINT_ASYNC_INIT(BookUpdate)
        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<BookDto>>(
                    controller->getDefaultObjectMapper()).callbackTo(&BookUpdate::returnBookResponse);
        }
        Action returnBookResponse( const oatpp::Object<BookDto>& body) {
            std::string token = request->getHeader("token") == nullptr ? "" : request->getHeader("token");
            JWTAuth auth;
            if (!auth.checkToken(token))
                return _return(controller->createResponse(Status::CODE_401));

            std::string role = auth.getRole(token);

            if (role != "admin")
                return _return(controller->createResponse(Status::CODE_403));


            std::shared_ptr<Book> book = std::shared_ptr<Book>(new Book(body->name,
                                                                        body->author,
                                                                        body->lib_id));
            book->setID(atoi(request->getPathVariable("id")->c_str()));

            try {
                manager->exec(std::shared_ptr<Command> (new UpdateBookCommand(ioc->getBookRepository(), ioc->getLibraryRepository(), book)), role);
            }
            catch (LogicException) {
                return _return(controller->createResponse(Status::CODE_500));
            }
            return _return(controller->createResponse(Status::CODE_200));
        }


    };


    ENDPOINT_INFO(BookPoint){
        info->summary = "create new book; call succeeds only if user is admin";

        info->headers.add<oatpp::String>("token");
        info->headers["token"].required = true;
        info->headers["token"].addExample("1", oatpp::String("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.ey"));

        info->addConsumes<Object<BookDto>>("application/json");

        info->addResponse(Status::CODE_401).description = "auth failed or no such user or credentials are not given";
        info->addResponse(Status::CODE_403).description = "role doesn't allow such actions";
        info->addResponse(Status::CODE_500).description = "internal error";
        info->addResponse(Status::CODE_200);
    };

    ENDPOINT_ASYNC("POST", "/api/v2/books", BookPoint) {

    ENDPOINT_ASYNC_INIT(BookPoint)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<BookDto>>(controller->getDefaultObjectMapper()).callbackTo(&BookPoint::returnResponse);
        }

        Action returnResponse(const oatpp::Object<BookDto>& body){
            std::string token = request->getHeader("token") == nullptr ? "" : request->getHeader("token");
            JWTAuth auth;
            if (!auth.checkToken(token))
                return _return(controller->createResponse(Status::CODE_401));

            std::string role = auth.getRole(token);

            if (role != "admin")
                return _return(controller->createResponse(Status::CODE_403));

            std::vector<std::shared_ptr<Book>> books;
            std::shared_ptr<Book> book = std::shared_ptr<Book>(new Book(body->name, body->author, body->lib_id));
            books.push_back(book);
            try{
                manager->exec(std::shared_ptr<Command>( new AddBooksCommand(ioc->getBookRepository(), ioc->getLibraryRepository(), books)), role);
            }
            catch (LogicException) {
                return _return(controller->createResponse(Status::CODE_500));
            }
            return _return(controller->createResponse(Status::CODE_200));
        }

    };


    ENDPOINT_INFO(BookDeletePoint){
        info->summary = "delete book with given identifier; call succeeds only if user is admin";

        info->headers.add<oatpp::String>("token");
        info->headers["token"].required = true;
        info->headers["token"].addExample("1", oatpp::String("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.ey"));

        info->pathParams.add<oatpp::Int64>("id").required = true;
        info->pathParams["id"].description = "identifier of the Book returned from GET Book request;";
        info->pathParams["id"].addExample("1", oatpp::String("23"));


        info->addResponse(Status::CODE_401).description = "auth failed or no such user or credentials are not given";
        info->addResponse(Status::CODE_403).description = "role doesn't allow such actions";
        info->addResponse(Status::CODE_500).description = "internal error";
        info->addResponse(Status::CODE_200).description = "update succeeded";
    };

    ENDPOINT_ASYNC("DELETE", "/api/v2/books/{id}", BookDeletePoint) {

    ENDPOINT_ASYNC_INIT(BookDeletePoint)

        Action act() override {
            std::string token = request->getHeader("token") == nullptr ? "" : request->getHeader("token");
            JWTAuth auth;
            if (!auth.checkToken(token))
                return _return(controller->createResponse(Status::CODE_401));

            std::string role = auth.getRole(token);

            if (role != "admin")
                return _return(controller->createResponse(Status::CODE_403));

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);
            int id;
            if (request->getPathVariable("id") != nullptr) {
                id = atoi(request->getPathVariable("id")->c_str());
                manager->exec(std::shared_ptr<Command>(new DeleteBooksCommand(ioc->getBookRepository(), id)), role);
                return _return(controller->createResponse(Status::CODE_200));
            }
            else
                return _return(controller->createResponse(Status::CODE_500));

        }

    };


    ENDPOINT_INFO(LibraryPoint){
        info->summary = "information about libraries (all filters applied in AND strategy)";

        info->headers.add<oatpp::String>("token");
        info->headers["token"].required = true;
        info->headers["token"].addExample("1", oatpp::String("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.ey"));

        info->queryParams.add<oatpp::String>("address").required = false;
        info->queryParams["address"].description = "address of libraries to be returned";
        info->queryParams["address"].addExample("1", oatpp::String("Smolenskii per, 1"));

        info->queryParams.add<oatpp::String>("name").required = false;
        info->queryParams["name"].description = "name of libraries to be returned";
        info->queryParams["name"].addExample("1", oatpp::String("Solnishko"));

        info->queryParams.add<oatpp::Int64>("id").required = false;
        info->queryParams["id"].description = "identifier of the Library";
        info->queryParams["id"].addExample("1", oatpp::String("22"));


        info->addResponse(Status::CODE_401).description = "auth failed or no such user or credentials are not given";
        info->addResponse(Status::CODE_500).description = "internal error";
        info->addResponse<Object<LibrariesDto>>(Status::CODE_200, "application/json");
    };

    ENDPOINT_ASYNC("GET", "/api/v2/libraries", LibraryPoint ) {

    ENDPOINT_ASYNC_INIT(LibraryPoint)

        Action act() override {

            std::string token = request->getHeader("token") == nullptr ? "" : request->getHeader("token");
            JWTAuth auth;
            if (!auth.checkToken(token))
                return _return(controller->createResponse(Status::CODE_401));

            std::string role = auth.getRole(token);

            std::vector<std::shared_ptr<Library>> libs;
            std::vector<std::shared_ptr<LibraryFilter>> filters;

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);


            if (queryParams.get("address") != nullptr) {
                std::string s = queryParams.get("address");
                filters.push_back(std::shared_ptr<LibraryFilter>(new ByAddressFilter(replaceAll(s, {"+", "%23","%40"}, {" ","#","@"}) )));
            }
            if (queryParams.get("name") != nullptr)
            {
                std::string s = queryParams.get("name");
                filters.push_back(std::shared_ptr<LibraryFilter>(new ByLibraryNameFilter(replaceAll(s, {"+", "%23","%40"}, {" ","#","@"}) )));
            }
            if (queryParams.get("id") != nullptr)
            {
                int id = std::atoi(queryParams.get("id")->c_str());
                filters.push_back(std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(id)));
            }
            try {
                manager->exec(
                        std::shared_ptr<Command>(new GetlibrariesCommand(ioc->getLibraryRepository(), libs, filters)),
                        role);
            }
            catch (LogicException) {
                return _return(controller->createResponse(Status::CODE_500));
            }
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


    ENDPOINT_INFO(LibraryUpdatePoint){
        info->summary = "update library with given identifier; call succeeds only if user is admin";

        info->headers.add<oatpp::String>("token");
        info->headers["token"].required = true;
        info->headers["token"].addExample("1", oatpp::String("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.ey"));

        info->pathParams.add<oatpp::Int64>("id").required = true;
        info->pathParams["id"].description = "identifier of the Library";
        info->pathParams["id"].addExample("1", oatpp::String("23"));

        info->addConsumes<Object<LibraryDto>>("application/json");

        info->addResponse(Status::CODE_401).description = "auth failed or no such user or credentials are not given";
        info->addResponse(Status::CODE_403).description = "role doesn't allow such actions";
        info->addResponse(Status::CODE_500).description = "internal error";
        info->addResponse(Status::CODE_200).description = "update succeeded";
    };

    ENDPOINT_ASYNC("PUT", "/api/v2/libraries/{id}", LibraryUpdatePoint ) {

    ENDPOINT_ASYNC_INIT(LibraryUpdatePoint)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<LibraryDto>>(
                    controller->getDefaultObjectMapper()).callbackTo(&LibraryUpdatePoint::returnLibraryResponse);
        }
        Action returnLibraryResponse( const oatpp::Object<LibraryDto>& body) {
            std::string token = request->getHeader("token") == nullptr ? "" : request->getHeader("token");
            JWTAuth auth;
            if (!auth.checkToken(token))
                return _return(controller->createResponse(Status::CODE_401));

            std::string role = auth.getRole(token);

            if (role != "admin")
                return _return(controller->createResponse(Status::CODE_403));

            std::shared_ptr<Library> lib = std::shared_ptr<Library>(new Library(body->name, body->address));
            lib->setID(atoi(request->getPathVariable("id")->c_str()));
            try {
                manager->exec(std::shared_ptr<Command>(new UpdateLibrariesCommand(ioc->getLibraryRepository(), lib)),
                              role);
            }
            catch (LogicException) {
                return _return(controller->createResponse(Status::CODE_500));
            }
            return _return(controller->createResponse(Status::CODE_200));
        }


    };


    ENDPOINT_INFO(LibraryPostPoint){
        info->summary = "create new library; call succeeds only if user is admin";

        info->headers.add<oatpp::String>("token");
        info->headers["token"].required = true;
        info->headers["token"].addExample("1", oatpp::String("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.ey"));

        info->addConsumes<Object<LibraryDto>>("application/json");

        info->addResponse(Status::CODE_401).description = "auth failed or no such user or credentials are not given";
        info->addResponse(Status::CODE_403).description = "role doesn't allow such actions";
        info->addResponse(Status::CODE_500).description = "internal error";
        info->addResponse(Status::CODE_200);
    };

    ENDPOINT_ASYNC("POST", "/api/v2/libraries", LibraryPostPoint ) {

    ENDPOINT_ASYNC_INIT(LibraryPostPoint)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<LibraryDto>>(
                    controller->getDefaultObjectMapper()).callbackTo(&LibraryPostPoint::returnLibraryResponse);
        }
        Action returnLibraryResponse( const oatpp::Object<LibraryDto>& body) {
            std::string token = request->getHeader("token") == nullptr ? "" : request->getHeader("token");
            JWTAuth auth;
            if (!auth.checkToken(token))
                return _return(controller->createResponse(Status::CODE_401));

            std::string role = auth.getRole(token);
            if (role != "admin")
                return _return(controller->createResponse(Status::CODE_403));

            std::shared_ptr<Library> lib = std::shared_ptr<Library>(new Library(body->name, body->address));

            try {
                manager->exec(std::shared_ptr<Command>(new PostLibrariesCommand(ioc->getLibraryRepository(), lib)),
                              role);
            }
            catch (LogicException) {
                    return _return(controller->createResponse(Status::CODE_500));
            }
            return _return(controller->createResponse(Status::CODE_200));
        }


    };


    ENDPOINT_INFO(LibraryDeletePoint){
        info->summary = "delete book with given identifier; call succeeds only if user is admin";

        info->headers.add<oatpp::String>("token");
        info->headers["token"].required = true;
        info->headers["token"].addExample("1", oatpp::String("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.ey"));


        info->pathParams.add<oatpp::Int64>("id").required = true;
        info->pathParams["id"].description = "identifier of the Library;";
        info->pathParams["id"].addExample("1", oatpp::String("23"));


        info->addResponse(Status::CODE_401).description = "auth failed or no such user or credentials are not given";
        info->addResponse(Status::CODE_403).description = "role doesn't allow such actions";
        info->addResponse(Status::CODE_500).description = "internal error";
        info->addResponse(Status::CODE_200).description = "update succeeded";
    };

    ENDPOINT_ASYNC("DELETE", "/api/v2/libraries/{id}", LibraryDeletePoint ) {

    ENDPOINT_ASYNC_INIT(LibraryDeletePoint)

        Action act() override {
            std::string token = request->getHeader("token") == nullptr ? "" : request->getHeader("token");
            JWTAuth auth;
            if (!auth.checkToken(token))
                return _return(controller->createResponse(Status::CODE_401));

            std::string role = auth.getRole(token);

            if (role != "admin")
                return _return(controller->createResponse(Status::CODE_403));

            String tail = request->getPathTail();
            auto queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);
            int id;
            if (request->getPathVariable("id") != nullptr) {
                id = atoi(request->getPathVariable("id")->c_str());
                try {
                    manager->exec(std::shared_ptr<Command>(new DeleteLibrariesCommand(ioc->getLibraryRepository(), id)),
                                  role);
                }
                catch (LogicException) {
                    return _return(controller->createResponse(Status::CODE_500));
                }
                return _return(controller->createResponse(Status::CODE_200));
            }
            return _return(controller->createResponse(Status::CODE_500));

        }

    };
    

    ENDPOINT_INFO(LoginPoint){
        info->summary = "login call";

        info->headers.add<oatpp::String>("login");
        info->headers["login"].required = true;
        info->headers["login"].addExample("1", oatpp::String("katya_varlamova"));

        info->headers.add<oatpp::String>("password").required = true;
        info->headers["password"].required = true;


        info->addResponse(Status::CODE_401).description = "auth failed or no such user or credentials are not given";
        info->addResponse(Status::CODE_500).description = "internal error";
        info->addResponse<Object<AccountDto>>(Status::CODE_200, "application/json").description = "auth succeeded";
    };

    ENDPOINT_ASYNC("GET", "/api/v2/accounts", LoginPoint) {

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
                return _return(controller->createResponse(Status::CODE_401));
            }

            JWTAuth auth;
            std::string token = auth.createToken(account->getLogin(), account->getRole());

            auto accDto = AccountDto::createShared();
            accDto->name = account->getName();
            accDto->id = account->getID();
            accDto->token = token;
            if (account->getRole() == "librarian") {
                std::shared_ptr<LibrarianAccount> lacc;
                try {
                    manager->exec(std::shared_ptr<Command>(
                            new GetLibrarianAccountCommand(ioc->getLibrarianAccountRepository(), lacc,
                                                           std::vector<std::shared_ptr<AccountFilter>>(
                                                                   {std::shared_ptr<AccountFilter>(
                                                                           new ByAccountIDFilter(account->getID()))}))),
                                  account->getRole());
                }
                catch (LogicException) {
                    return _return(controller->createResponse(Status::CODE_500));
                }

                auto laccDto = LibrarianAccountDTO::createShared();
                laccDto->lib_id = lacc->getLibraryID();
                accDto->librarian_acc = laccDto;
            }
            if (account->getRole() == "reader")
            {
                std::shared_ptr<ReaderAccount> racc;
                try {
                    manager->exec(std::shared_ptr<Command>(
                            new GetReaderAccountCommand(ioc->getReaderAccountRepository(), racc,
                                                        std::vector<std::shared_ptr<AccountFilter>>(
                                                                {std::shared_ptr<AccountFilter>(
                                                                        new ByAccountIDFilter(account->getID()))}))),
                                  account->getRole());
                }
                catch (LogicException) {
                    return _return(controller->createResponse(Status::CODE_500));
                }
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



    ENDPOINT_INFO(RegistrationPoint){
        info->summary = "registration call";

        info->headers.add<oatpp::String>("login");
        info->headers["login"].required = true;
        info->headers["login"].addExample("1", oatpp::String("katya_varlamova"));

        info->headers.add<oatpp::String>("password").required = true;
        info->headers["password"].required = true;

        info->headers.add<oatpp::String>("role");
        info->headers["role"].required = true;
        info->headers["role"].addExample("1", oatpp::String("reader"));
        info->headers["role"].description = "reader/admin/librarian";

        info->addConsumes<Object<AccountDto>>("application/json");

        info->addResponse(Status::CODE_401).description = "auth failed or no such user or credentials are not given";
        info->addResponse(Status::CODE_500).description = "internal error";
        info->addResponse(Status::CODE_200).description = "registration succeeded";
    };

    ENDPOINT_ASYNC("POST", "/api/v2/accounts", RegistrationPoint) {

    ENDPOINT_ASYNC_INIT(RegistrationPoint)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<AccountDto>>(
                    controller->getDefaultObjectMapper()).callbackTo(&RegistrationPoint::returnResponse);
        }

        Action returnResponse(const oatpp::Object<AccountDto> &body) {
            std::string role = request->getHeader("role") == nullptr ? "" : request->getHeader("role");
            std::string login = request->getHeader("login") == nullptr ? "" : request->getHeader("login");
            std::string pwd = request->getHeader("password") == nullptr ? "" : request->getHeader("password");
            printf("%s", (role + " " + login + " " + pwd).c_str());
            if (login.empty() || pwd.empty() || role.empty())
                return _return(controller->createResponse(Status::CODE_401));

            if (role == "admin") {

                manager->registration(std::shared_ptr<AdminAccount>(
                        new AdminAccount(std::shared_ptr<Account>(new Account(login,
                                                                              pwd,
                                                                              role,
                                                                              body->name)))));
            }
            if (role == "librarian") {
                manager->registration(std::shared_ptr<LibrarianAccount>(
                        new LibrarianAccount(std::shared_ptr<Account>(new Account(login,
                                                                              pwd,
                                                                              role,
                                                                              body->name)), body->librarian_acc->lib_id)));

            }
            if (role == "reader") {
                manager->registration(std::shared_ptr<ReaderAccount>(new ReaderAccount (std::shared_ptr<Account>(new Account(login,
                                                                                                                                   pwd,
                                                                                                                                   role,
                                                                                                                                   body->name)),
                                                                                             body->reader_acc->phone)));

            }
            return _return(controller->createResponse(Status::CODE_200));
        }

    };

    /**
     *  Echo body endpoint Coroutine. Mapped to "/body/dto".
     *  Deserialize DTO reveived, and return same DTO
     *  Returns body as MessageDto received in the request
     */

    static std::shared_ptr<DataAccessManagerRest> manager;
    static std::shared_ptr<IIocRepository> ioc;
};

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- End codegen

#endif //SRC_SERVERCONTROLLERRESTAPI_H
