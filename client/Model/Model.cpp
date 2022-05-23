//
// Created by Екатерина on 16.05.2022.
//

#include "Model.h"
int Model::registration(const std::shared_ptr<AdminAccount> &account)
{
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    auto aaccDto = AdminAccountDTO::createShared();
    auto accDto = AccountDto::createShared();
    accDto->name = account->getAccount()->getName();
    accDto->login = account->getAccount()->getLogin();
    accDto->password = account->getAccount()->getPassword();
    accDto->role = account->getAccount()->getRole();
    accDto->admin_acc = aaccDto;

    auto r = client->registration("admin", objectMapper->writeToString(accDto));
    if (r->getStatusCode() == 200)
        return 0;
    return 1;

}
int Model::registration(const std::shared_ptr<ReaderAccount> &racc)
{
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    auto raccDto = ReaderAccountDTO::createShared();
    auto accDto = AccountDto::createShared();
    accDto->name = racc->getAccount()->getName();
    accDto->login = racc->getAccount()->getLogin();
    accDto->password = racc->getAccount()->getPassword();
    accDto->role = racc->getAccount()->getRole();
    raccDto->phone = racc->getPhone();
    accDto->reader_acc = raccDto;

    auto r = client->registration("reader", objectMapper->writeToString(accDto));
    if (r->getStatusCode() == 200)
        return 0;
    return 1;
}
int Model::registration(const std::shared_ptr<LibrarianAccount> &lacc)
{
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    auto laccDto = LibrarianAccountDTO::createShared();
    auto accDto = AccountDto::createShared();
    accDto->name = lacc->getAccount()->getName();
    accDto->login = lacc->getAccount()->getLogin();
    accDto->password = lacc->getAccount()->getPassword();
    accDto->role = lacc->getAccount()->getRole();
    laccDto->lib_id = lacc->getLibraryID();
    accDto->librarian_acc = laccDto;

    auto r = client->registration("librarian", objectMapper->writeToString(accDto));
    if (r->getStatusCode() == 200)
        return 0;
    return 1;
}
std::shared_ptr<LibrarianAccount> Model::getLibrarianAccount(const std::string &log, const std::string &pass)
{
    std::shared_ptr<LibrarianAccount> lacc;
    std::shared_ptr<Account> account;
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    auto r = client->login(log, pass);
    if (r->getStatusCode() == 200){
        auto res = r->readBodyToDto<oatpp::Object<AccountDto>>(objectMapper);
        account = std::shared_ptr<Account>(new Account(res->login,
                                                       res->password,
                                                       res->role,
                                                       res->name));
        lacc = std::shared_ptr<LibrarianAccount>(new LibrarianAccount(account, res->librarian_acc->lib_id));
    }
    return lacc;
}
std::shared_ptr<ReaderAccount> Model::getReaderAccount(const std::string &log, const std::string &pass)
{
    std::shared_ptr<ReaderAccount> racc;
    std::shared_ptr<Account> account;
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    auto r = client->login(log, pass);
    if (r->getStatusCode() == 200){
        auto res = r->readBodyToDto<oatpp::Object<AccountDto>>(objectMapper);
        account = std::shared_ptr<Account>(new Account(res->login,
                                                       res->password,
                                                       res->role,
                                                       res->name));
        racc = std::shared_ptr<ReaderAccount>(new ReaderAccount(account, res->reader_acc->phone));
    }
    return racc;
}
std::shared_ptr<Account> Model::login(const std::string &login, const std::string &pass)
{
    std::shared_ptr<Account> account;
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    auto r = client->login(login, pass);
    if (r->getStatusCode() == 200){
        auto res = r->readBodyToDto<oatpp::Object<AccountDto>>(objectMapper);
        account = std::shared_ptr<Account>(new Account(res->login,
                                                       res->password,
                                                       res->role,
                                                       res->name));
    }
    return account;
}
int Model::addLibrary(const std::string &login, const std::string &pass, const std::shared_ptr<Library> &library)
{
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    auto libDto = LibraryDto::createShared();
    libDto->name = library->getName();
    libDto->address = library->getAddress();
    libDto->id = -1;

    auto r = client->addLibrary(login, pass, objectMapper->writeToString(libDto));
    if (r->getStatusCode() == 200)
        return 0;
    return 1;
}
std::vector<std::shared_ptr<Library>> Model::getLibraries(const std::string &login, const std::string &pass, int id,
                                                          std::string name, std::string address) {
    std::vector<std::shared_ptr<Library>> libs;
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    auto r = client->getLibraries(login, pass);
    if (id != -1) {
        r = client->getLibrariesByID(login, pass, id);
    } else {
        if (name != "") {
            if (address != "")
                r = client->getLibrariesByAddressName(login, pass, name, address);
            else
                r = client->getBooksByName(login, pass, name);
        } else {
            if (address != "")
                r = client->getLibrariesByAddress(login, pass, address);
        }
    }
    if (r->getStatusCode() == 200){
        auto res = r->readBodyToDto<oatpp::Object<LibrariesDto>>(objectMapper);

        for (int i = 0; i < res->libraries->size(); i++)
        {
            std::shared_ptr<Library> l = std::shared_ptr<Library>(new Library(res->libraries[i]->name,
                                                                              res->libraries[i]->address));
            l->setID(res->libraries[i]->id);
            libs.push_back(l);
        }
    }
    if (id != -1 && !libs.empty())
    {
        if (name != "" && libs[0]->getName() != name ||
                address != "" && libs[0]->getAddress() != address)
            return std::vector<std::shared_ptr<Library>>();
    }
    return libs;
}
int Model::deleteLibrary(const std::string &login, const std::string &pass, int id)
{
    auto r = client->deleteLibrary(id, login, pass, id);
    if (r->getStatusCode() == 200)
        return 0;
    return 1;
}
int Model::updateLibrary(const std::string &login, const std::string &pass, const std::shared_ptr<Library> &library)
{
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    auto libDto = LibraryDto::createShared();
    libDto->name = library->getName();
    libDto->address = library->getAddress();
    libDto->id = library->getID();

    auto r = client->updateLibrary(library->getID(), login, pass, objectMapper->writeToString(libDto));
    if (r->getStatusCode() == 200)
        return 0;
    return 1;
}
int Model::addBook(const std::string &login, const std::string &pass, const std::shared_ptr<Book> &book) {
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    auto bookDto = BookDto::createShared();

    bookDto->name = book->getName();
    bookDto->author = book->getAuthor();
    bookDto->id = -1;
    bookDto->lib_id = book->getLibraryID();

    auto r = client->addBook(login, pass, objectMapper->writeToString(bookDto));
    if (r->getStatusCode() == 200)
        return 0;
    return 1;
}
int Model::updateBook(const std::string &login, const std::string &pass, const std::shared_ptr<Book> &book)
{
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    auto bookDto = BookDto::createShared();
    bookDto->name = book->getName();
    bookDto->author = book->getAuthor();
    bookDto->id = book->getID();
    bookDto->lib_id = book->getLibraryID();

    auto r = client->updateBook(book->getID(), login, pass, objectMapper->writeToString(bookDto));
    if (r->getStatusCode() == 200)
        return 0;
    return 1;
}
int Model::deleteBook(const std::string &login, const std::string &pass, int id)
{
    auto r = client->deleteBook(id, login, pass, id);
    if (r->getStatusCode() == 200)
        return 0;
    return 1;
}
std::vector<std::shared_ptr<Book>> Model::getBooks(const std::string &login, const std::string &pass, std::string name, std::string author, bool l, bool f)
{
    std::vector<std::shared_ptr<Book>> books;
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    auto r = client->getBooks(login, pass);
    if (!l) {
        if (!f) {
            if (name != "") {
                if (author != "")
                    r = client->getBooksByNameAuthor(login, pass, name, author);
                else
                    r = client->getBooksByName(login, pass, name);
            } else {
                if (author != "")
                    r = client->getBooksByAuthor(login, pass, author);
            }
        } else {
            if (name != "") {
                if (author != "")
                    r = client->getBooksByNameAuthorFree(login, pass, name, author, 1);
                else
                    r = client->getBooksByNameFree(login, pass, name, 1);
            } else {
                if (author != "")
                    r = client->getBooksByAuthorFree(login, pass, author, 1);
                else
                    r = client->getBooksFree(login, pass, 1);
            }
        }
    }
    else
    {
        if (name != "")
        {
            if (author != "")
                r = client->getBooksByNameAuthorLogin(login, pass, name, author, login);
            else
                r = client->getBooksByNameLogin(login, pass, name, login);
        }
        else
        {
            if (author != "")
                r = client->getBooksByAuthorLogin(login, pass, author, login);
            else
                r = client->getBooksByLogin(login, pass, login);
        }
    }
    if (r->getStatusCode() == 200){
        auto res = r->readBodyToDto<oatpp::Object<BooksDto>>(objectMapper);

        for (int i = 0; i < res->books->size(); i++)
        {
            std::shared_ptr<Book> b = std::shared_ptr<Book>(new Book(res->books[i]->name,
                                                                     res->books[i]->author,
                                                                     res->books[i]->lib_id,
                                                                     res->books[i]->login));
            b->setID(res->books[i]->id);
            books.push_back(b);
        }
    }
    return books;
}
int Model::giveReturnBook(const std::string &login, const std::string &pass, const std::string &login_user, int book_id, std::string action)
{
    auto r = client->giveReturnBook(book_id, login, pass, book_id, login_user, action);
    if (r->getStatusCode() == 200)
        return 0;
    return 1;
}

int Model::addEBook(const std::string &login, const std::string &pass, const std::shared_ptr<EBook> &book) {
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    auto bookDto = EBookDto::createShared();

    bookDto->name = book->getName();
    bookDto->author = book->getAuthor();
    bookDto->id = -1;
    bookDto->link = book->getLink();

    auto r = client->addBook(login, pass, objectMapper->writeToString(bookDto));
    if (r->getStatusCode() == 200)
        return 0;
    return 1;
}
int Model::updateEBook(const std::string &login, const std::string &pass, const std::shared_ptr<EBook> &book)
{
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    auto bookDto = EBookDto::createShared();
    bookDto->name = book->getName();
    bookDto->author = book->getAuthor();
    bookDto->id = book->getID();
    bookDto->link = book->getLink();

    auto r = client->updateBook(book->getID(), login, pass, objectMapper->writeToString(bookDto));
    if (r->getStatusCode() == 200)
        return 0;
    return 1;
}
int Model::deleteEBook(const std::string &login, const std::string &pass, int id)
{
    auto r = client->deleteEBook(id, login, pass, id);
    if (r->getStatusCode() == 200)
        return 0;
    return 1;
}
std::vector<std::shared_ptr<EBook>> Model::getEBooks(const std::string &login, const std::string &pass, std::string name, std::string author)
{
    std::vector<std::shared_ptr<EBook>> books;
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    auto r = client->getBooks(login, pass);
    if (name != "") {
        if (author != "")
            r = client->getBooksByNameAuthor(login, pass, name, author);
        else
            r = client->getBooksByName(login, pass, name);
    } else {
        if (author != "")
            r = client->getBooksByAuthor(login, pass, author);
    }
    if (r->getStatusCode() == 200){
        auto res = r->readBodyToDto<oatpp::Object<EBooksDto>>(objectMapper);

        for (int i = 0; i < res->books->size(); i++)
        {
            std::shared_ptr<EBook> b = std::shared_ptr<EBook>(new EBook(res->books[i]->name,
                                                                     res->books[i]->author,
                                                                     res->books[i]->link));
            b->setID(res->books[i]->id);
            books.push_back(b);
        }
    }
    return books;
}