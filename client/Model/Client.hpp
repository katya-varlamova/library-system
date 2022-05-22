#ifndef DemoApiClient_hpp
#define DemoApiClient_hpp

#include "DTOs.hpp"
#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

class Client : public oatpp::web::client::ApiClient {
#include OATPP_CODEGEN_BEGIN(ApiClient)

API_CLIENT_INIT(Client)


      API_CALL("GET", "/api/v1/login", login,  HEADER(String, login), HEADER(String, password))
      API_CALL("POST", "/api/v1/registration", registration, QUERY(String, role), BODY_STRING(String, body))

      API_CALL("POST", "/api/v1/library", addLibrary,  HEADER(String, login), HEADER(String, password), BODY_STRING(String, body))
      API_CALL("DELETE", "/api/v1/library", deleteLibrary,  HEADER(String, login), HEADER(String, password), QUERY(Int64, id))
      API_CALL("PUT", "/api/v1/library", updateLibrary,  HEADER(String, login), HEADER(String, password), BODY_STRING(String, body))
      API_CALL("GET", "/api/v1/library", getLibraries,  HEADER(String, login), HEADER(String, password))
      API_CALL("GET", "/api/v1/library", getLibrariesByName,  HEADER(String, login), HEADER(String, password), QUERY(String, name))
      API_CALL("GET", "/api/v1/library", getLibrariesByAddress,  HEADER(String, login), HEADER(String, password), QUERY(String, address))
      API_CALL("GET", "/api/v1/library", getLibrariesByAddressName,  HEADER(String, login), HEADER(String, password), QUERY(String, name),  QUERY(String, address))
      API_CALL("GET", "/api/v1/library", getLibrariesByID,  HEADER(String, login), HEADER(String, password), QUERY(Int64, id))

      API_CALL("POST", "/api/v1/book", addBook,  HEADER(String, login), HEADER(String, password), BODY_STRING(String, body))
      API_CALL("DELETE", "/api/v1/book", deleteBook,  HEADER(String, login), HEADER(String, password), QUERY(Int64, id))
      API_CALL("PUT", "/api/v1/book", updateBook,  HEADER(String, login), HEADER(String, password), BODY_STRING(String, body))
      API_CALL("PUT", "/api/v1/book/give", giveBook,  HEADER(String, login), HEADER(String, password), QUERY(Int64, book_id), QUERY(String, login_user))
      API_CALL("PUT", "/api/v1/book/return", returnBook,  HEADER(String, login), HEADER(String, password), QUERY(Int64, book_id), QUERY(String, login_user))

      API_CALL("GET", "/api/v1/book", getBooks,  HEADER(String, login), HEADER(String, password))
      API_CALL("GET", "/api/v1/book", getBooksByName,  HEADER(String, login), HEADER(String, password), QUERY(String, name))
      API_CALL("GET", "/api/v1/book", getBooksByAuthor,  HEADER(String, login), HEADER(String, password), QUERY(String, author))
      API_CALL("GET", "/api/v1/book", getBooksByNameAuthor,  HEADER(String, login), HEADER(String, password), QUERY(String, name),  QUERY(String, author))
      API_CALL("GET", "/api/v1/book", getBooksFree,  HEADER(String, login), HEADER(String, password), QUERY(Int8, free))
      API_CALL("GET", "/api/v1/book", getBooksByNameFree,  HEADER(String, login), HEADER(String, password), QUERY(String, name), QUERY(Int8, free))
      API_CALL("GET", "/api/v1/book", getBooksByAuthorFree,  HEADER(String, login), HEADER(String, password), QUERY(String, author), QUERY(Int8, free))
      API_CALL("GET", "/api/v1/book", getBooksByNameAuthorFree,  HEADER(String, login), HEADER(String, password), QUERY(String, name),  QUERY(String, author), QUERY(Int8, free))

      API_CALL("GET", "/api/v1/book", getBooksByLogin,  HEADER(String, login), HEADER(String, password), QUERY(String, login_filter))
      API_CALL("GET", "/api/v1/book", getBooksByNameLogin,  HEADER(String, login), HEADER(String, password), QUERY(String, name), QUERY(String, login_filter))
      API_CALL("GET", "/api/v1/book", getBooksByAuthorLogin,  HEADER(String, login), HEADER(String, password), QUERY(String, author), QUERY(String, login_filter))
      API_CALL("GET", "/api/v1/book", getBooksByNameAuthorLogin,  HEADER(String, login), HEADER(String, password), QUERY(String, name),  QUERY(String, author), QUERY(String, login_filter))
#include OATPP_CODEGEN_END(ApiClient)
};

#endif /* DemoApiClient_hpp */