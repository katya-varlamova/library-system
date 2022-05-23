//
// Created by Екатерина on 16.05.2022.
//

#ifndef INTERFACE_MODEL_H
#define INTERFACE_MODEL_H
#include "Client.hpp"
#include "oatpp-curl/RequestExecutor.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp/network/tcp/client/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "Entities/Account/AdminAccount.h"
#include "Entities/Account/LibrarianAccount.h"
#include "Entities/Account/ReaderAccount.h"
#include "Entities/Book/Book.h"
#include "Entities/EBook/EBook.h"
class Model {
public:
    Model()
    {
        auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
        auto connectionProvider = oatpp::network::tcp::client::ConnectionProvider::createShared({"127.0.0.1", 8000});
        auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(connectionProvider);
        client = Client::createShared(requestExecutor, objectMapper);
    }
    int registration(const std::shared_ptr<ReaderAccount> &reader);
    int registration(const std::shared_ptr<LibrarianAccount> &librarian);
    int registration(const std::shared_ptr<AdminAccount> &admin);
    std::shared_ptr<Account> login(const std::string &login, const std::string &pass);
    std::shared_ptr<LibrarianAccount> getLibrarianAccount(const std::string &login, const std::string &pass);
    std::shared_ptr<ReaderAccount> getReaderAccount(const std::string &login, const std::string &pass);

    int addLibrary(const std::string &login, const std::string &pass, const std::shared_ptr<Library> &library);
    int updateLibrary(const std::string &login, const std::string &pass, const std::shared_ptr<Library> &library);
    int deleteLibrary(const std::string &login, const std::string &pass, int id);
    std::vector<std::shared_ptr<Library>> getLibraries(const std::string &login, const std::string &pass, int id = -1, std::string name = "", std::string address = "");


    int addBook(const std::string &login, const std::string &pass, const std::shared_ptr<Book> &book);
    int updateBook(const std::string &login, const std::string &pass, const std::shared_ptr<Book> &book);
    int deleteBook(const std::string &login, const std::string &pass, int id);
    std::vector<std::shared_ptr<Book>> getBooks(const std::string &login, const std::string &pass, std::string name = "", std::string author = "", bool l = false, bool f = false);
    int giveReturnBook(const std::string &login, const std::string &pass, const std::string &login_user, int book_id, std::string action);

    int addEBook(const std::string &login, const std::string &pass, const std::shared_ptr<EBook> &book);
    int updateEBook(const std::string &login, const std::string &pass, const std::shared_ptr<EBook> &book);
    int deleteEBook(const std::string &login, const std::string &pass, int id);
    std::vector<std::shared_ptr<EBook>> getEBooks(const std::string &login, const std::string &pass, std::string name = "", std::string author = "");
private:
    std::shared_ptr<Client> client;
};


#endif //INTERFACE_MODEL_H
