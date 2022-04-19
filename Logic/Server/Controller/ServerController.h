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

/**
 *  EXAMPLE ApiController
 *  Basic examples of howto create ENDPOINTs
 *  More details on oatpp.io
 */
class ServerController : public oatpp::web::server::api::ApiController {
protected:
    ServerController(const std::shared_ptr<ObjectMapper>& objectMapper)
            : oatpp::web::server::api::ApiController(objectMapper)
    {
    }
public:

    /**
     *  Inject @objectMapper component here as default parameter
     *  Do not return bare Controllable* object! use shared_ptr!
     */
    static std::shared_ptr<ServerController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>,
                                                                      objectMapper)){
        return std::shared_ptr<ServerController>(new ServerController(objectMapper));
    }

    /**
     *  Hello World endpoint Coroutine mapped to the "/" (root)
//     */
//    ENDPOINT_ASYNC("GET", "/", Root) {
//
//    ENDPOINT_ASYNC_INIT(Root)
//
//        /**
//         *  Coroutine entrypoint act()
//         *  returns Action (what to do next)
//         */
//        Action act() override {
//            auto dto = HelloDto::createShared();
//            dto->message = "Hello Async!";
//            dto->server = Header::Value::SERVER;
//            dto->userAgent = request->getHeader(Header::USER_AGENT);
//            return _return(controller->createDtoResponse(Status::CODE_200, dto));
//        }
//
//    };

    /**
     *  Echo body endpoint Coroutine. Mapped to "/body/string".
     *  Returns body received in the request
     */
//    ENDPOINT_ASYNC("GET", "/body/string", EchoStringBody) {
//
//        ENDPOINT_ASYNC_INIT(EchoStringBody)
//
//        Action act() override {
//                /* return Action to start child coroutine to read body */
//                return request->readBodyToStringAsync().callbackTo(&EchoStringBody::returnResponse);
//        }
//
//        Action returnResponse(const oatpp::String& body){
//            /* return Action to return created OutgoingResponse */
//            return _return(controller->createResponse(Status::CODE_200, body));
//        }
//
//    };

    ENDPOINT_ASYNC("GET", "/api/v1/free_books", FreeBooks ) {

        ENDPOINT_ASYNC_INIT(FreeBooks)

        Action act() override {

            std::string login = request->getQueryParameters().get("login") == nullptr ? "" : request->getQueryParameters().get("login");
            std::string pwd = request->getQueryParameters().get("password") == nullptr ? "" : request->getQueryParameters().get("password");
            std::string author = request->getQueryParameters().get("author") == nullptr ? "" : request->getQueryParameters().get("author");
            std::string lib_name = request->getQueryParameters().get("lib_name") == nullptr ? "" : request->getQueryParameters().get("lib_name");
            std::string name = request->getQueryParameters().get("name") == nullptr ? "" : request->getQueryParameters().get("name");

            if (login.empty() || pwd.empty())
                return _return(controller->createResponse(Status::CODE_300));
            std::vector<std::shared_ptr<Book>> books;
            if (!author.empty() && name.empty() && lib_name.empty())
                manager->exec(std::shared_ptr<GetFreeBooksByAuthorCommand> (new GetFreeBooksByAuthorCommand(books, author)), login, pwd);
            if (author.empty() && !name.empty() && lib_name.empty())
                manager->exec(std::shared_ptr<GetFreeBooksByNameCommand> (new GetFreeBooksByNameCommand(books, name)), login, pwd);
            auto booksDto = BooksDto::createShared();
            oatpp::Vector<oatpp::Object<BookDto>> booksVector ({});

            for (auto &book : books) {
                auto bookDto = BookDto::createShared();
                bookDto->name = book->getName();
                bookDto->author = book->getAuthor();
                bookDto->library_address = book->getLibrary()->getAddress();
                bookDto->library_name = book->getLibrary()->getName();

                booksVector->push_back(bookDto);
            }

            booksDto->books = booksVector;
            /* return Action to start child coroutine to read body */
            return _return(controller->createDtoResponse(Status::CODE_200, booksDto));
        }


    };
    ENDPOINT_ASYNC("PUT", "/api/v1/book", BookPoint) {

    ENDPOINT_ASYNC_INIT(BookPoint)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<BookDto>>(controller->getDefaultObjectMapper()).callbackTo(&BookPoint::returnResponse);
        }

        Action returnResponse(const oatpp::Object<BookDto>& body){
            std::string login = request->getQueryParameters().get("login") == nullptr ? "" : request->getQueryParameters().get("login");
            std::string pwd = request->getQueryParameters().get("password") == nullptr ? "" : request->getQueryParameters().get("password");
            std::vector<std::shared_ptr<Book>> books;
            std::shared_ptr<Library> library = std::shared_ptr<Library>(new Library(body->library_name, body->library_address));
            std::shared_ptr<Book> book = std::shared_ptr<Book>(new Book(body->name, body->author, library));
            books.push_back(book);
            manager->exec(std::shared_ptr<Command>(new AddBooksCommand(books)), login, pwd);
            return _return(controller->createResponse(Status::CODE_200));
        }

    };

    ENDPOINT_ASYNC("PUT", "/api/v1/registration", RegistrationPoint) {

    ENDPOINT_ASYNC_INIT(RegistrationPoint)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<AccountDto>>(controller->getDefaultObjectMapper()).callbackTo(&RegistrationPoint::returnResponse);
        }

        Action returnResponse(const oatpp::Object<AccountDto>& body){
        try {
            manager->registration(std::shared_ptr<Account>(new Account(body->login,
                                                                       body->password,
                                                                       body->role,
                                                                       body->name)));
        }
        catch (LogicException)
        {
            return _return(controller->createResponse(Status::CODE_500));
        }
            return _return(controller->createResponse(Status::CODE_200));
        }

    };

    ENDPOINT_ASYNC("GET", "/api/v1/login", LoginPoint) {

    ENDPOINT_ASYNC_INIT(LoginPoint)

        Action act() override {
            std::string login = request->getQueryParameters().get("login") == nullptr ? "" : request->getQueryParameters().get("login");
            std::string pwd = request->getQueryParameters().get("password") == nullptr ? "" : request->getQueryParameters().get("password");
            try {
                manager->login(login, pwd);
            }
            catch (LogicException)
            {
                return _return(controller->createResponse(Status::CODE_500));
            }
            return _return(controller->createResponse(Status::CODE_200));

    }

    };
    /**
     *  Echo body endpoint Coroutine. Mapped to "/body/dto".
     *  Deserialize DTO reveived, and return same DTO
     *  Returns body as MessageDto received in the request
     */
//    ENDPOINT_ASYNC("GET", "/body/dto", EchoDtoBody) {
//
//    ENDPOINT_ASYNC_INIT(EchoDtoBody)
//
//        Action act() override {
//            return request->readBodyToDtoAsync<oatpp::Object<MessageDto>>(controller->getDefaultObjectMapper()).callbackTo(&EchoDtoBody::returnResponse);
//        }
//
//        Action returnResponse(const oatpp::Object<MessageDto>& body){
//            return _return(controller->createDtoResponse(Status::CODE_200, body));
//        }
//
//    };

    static std::shared_ptr<DataAccessManager> manager;
};

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- End codegen

#endif //SRC_SERVERCONTROLLER_H
