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

      API_CALL("POST", "/api/v1/libraries/{id}", addLibrary,  HEADER(String, login), HEADER(String, password), BODY_STRING(String, body))
      API_CALL("DELETE", "/api/v1/libraries/{id}", deleteLibrary, PATH(Int64, id), HEADER(String, login), HEADER(String, password), QUERY(Int64, iid))
      API_CALL("PUT", "/api/v1/libraries/{id}", updateLibrary,  PATH(Int64, id), HEADER(String, login), HEADER(String, password), BODY_STRING(String, body))
      API_CALL("GET", "/api/v1/libraries", getLibraries,  HEADER(String, login), HEADER(String, password))
      API_CALL("GET", "/api/v1/libraries", getLibrariesByName,  HEADER(String, login), HEADER(String, password), QUERY(String, name))
      API_CALL("GET", "/api/v1/libraries", getLibrariesByAddress,  HEADER(String, login), HEADER(String, password), QUERY(String, address))
      API_CALL("GET", "/api/v1/libraries", getLibrariesByAddressName,  HEADER(String, login), HEADER(String, password), QUERY(String, name),  QUERY(String, address))
      API_CALL("GET", "/api/v1/libraries", getLibrariesByID,  HEADER(String, login), HEADER(String, password), QUERY(Int64, id))

      API_CALL("POST", "/api/v1/books", addBook,  HEADER(String, login), HEADER(String, password), BODY_STRING(String, body))
      API_CALL("DELETE", "/api/v1/books/{id}", deleteBook, PATH(Int64, id), HEADER(String, login), HEADER(String, password), QUERY(Int64, iid))
      API_CALL("PUT", "/api/v1/books/{id}", updateBook, PATH(Int64, id), HEADER(String, login), HEADER(String, password), BODY_STRING(String, body))
      API_CALL("PATCH", "/api/v1/books/{id}", giveReturnBook, PATH(Int64, id), HEADER(String, login), HEADER(String, password), QUERY(Int64, book_id), QUERY(String, login_user), QUERY(String, action))

      API_CALL("GET", "/api/v1/books", getBooks,  HEADER(String, login), HEADER(String, password))
      API_CALL("GET", "/api/v1/books", getBooksByName,  HEADER(String, login), HEADER(String, password), QUERY(String, name))
      API_CALL("GET", "/api/v1/books", getBooksByAuthor,  HEADER(String, login), HEADER(String, password), QUERY(String, author))
      API_CALL("GET", "/api/v1/books", getBooksByNameAuthor,  HEADER(String, login), HEADER(String, password), QUERY(String, name),  QUERY(String, author))
      API_CALL("GET", "/api/v1/books", getBooksFree,  HEADER(String, login), HEADER(String, password), QUERY(Int8, free))
      API_CALL("GET", "/api/v1/books", getBooksByNameFree,  HEADER(String, login), HEADER(String, password), QUERY(String, name), QUERY(Int8, free))
      API_CALL("GET", "/api/v1/books", getBooksByAuthorFree,  HEADER(String, login), HEADER(String, password), QUERY(String, author), QUERY(Int8, free))
      API_CALL("GET", "/api/v1/books", getBooksByNameAuthorFree,  HEADER(String, login), HEADER(String, password), QUERY(String, name),  QUERY(String, author), QUERY(Int8, free))

      API_CALL("GET", "/api/v1/books", getBooksByLogin,  HEADER(String, login), HEADER(String, password), QUERY(String, login_filter))
      API_CALL("GET", "/api/v1/books", getBooksByNameLogin,  HEADER(String, login), HEADER(String, password), QUERY(String, name), QUERY(String, login_filter))
      API_CALL("GET", "/api/v1/books", getBooksByAuthorLogin,  HEADER(String, login), HEADER(String, password), QUERY(String, author), QUERY(String, login_filter))
      API_CALL("GET", "/api/v1/books", getBooksByNameAuthorLogin,  HEADER(String, login), HEADER(String, password), QUERY(String, name),  QUERY(String, author), QUERY(String, login_filter))

      API_CALL("POST", "/api/v1/ebooks", addEBook,  HEADER(String, login), HEADER(String, password), BODY_STRING(String, body))
      API_CALL("GET", "/api/v1/ebooks", getEBooks,  HEADER(String, login), HEADER(String, password))
      API_CALL("GET", "/api/v1/ebooks", getEBooksByName,  HEADER(String, login), HEADER(String, password), QUERY(String, name))
      API_CALL("GET", "/api/v1/ebooks", getEBooksByAuthor,  HEADER(String, login), HEADER(String, password), QUERY(String, author))
      API_CALL("DELETE", "/api/v1/ebooks/{id}", deleteEBook, PATH(Int64, id), HEADER(String, login), HEADER(String, password), QUERY(Int64, iid))
      API_CALL("PUT", "/api/v1/ebooks/{id}", updateEBook, PATH(Int64, id), HEADER(String, login), HEADER(String, password), BODY_STRING(String, body))
#include OATPP_CODEGEN_END(ApiClient)
};

#endif /* DemoApiClient_hpp */