//
// Created by Екатерина on 27.03.2022.
//

#include "BookRepository.h"
#include "../DBAccount/AccountRepository.h"
#include "../DBAccount/AccountFilters/AccountFilter.h"
#include "../DBAccount/AccountFilters/ByAccountIDFilter.h"
#include "../DBAccount/AccountSpecifications/GetAccount.h"
#include "../../../Logger/Logger.h"

std::vector<std::shared_ptr<Book>> BookRepository::query(std::shared_ptr<Session> session, std::shared_ptr<BookSpecification> specification)
{
    std::vector<DBBook> dbb = specification->exec(session);
    std::vector<std::shared_ptr<Book>> vec;
    BookConverter converter;
    LibraryRepository lib_rep;
    std::vector<std::shared_ptr<LibraryFilter>> lfs;
    AccountRepository acc_rep;
    std::vector<std::shared_ptr<AccountFilter>> afs;
    for (auto &i : dbb) {
        lfs = {std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(i.get_lib_id()))};
        afs = {std::shared_ptr<AccountFilter>(new ByAccountIDFilter(i.get_acc_id()))};
        auto res = lib_rep.query(session, std::shared_ptr<LibarySpecification>(new GetLibrary(lfs)));
        auto res2 = acc_rep.query(session, std::shared_ptr<AccountSpecification>(new GetAccount(afs)));
        if (!res.empty()) {
            if (!res2.empty())
                vec.push_back(converter.convert(i, i.get_lib_id(), res2[0]->getLogin()));
            else
                vec.push_back(converter.convert(i, i.get_lib_id(), ""));
        }
    }
    return vec;
}
void BookRepository::addBook(std::shared_ptr<Session> session, std::shared_ptr<Book> book)
{
    std::vector<std::shared_ptr<LibraryFilter>> lfs = {std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(book->getLibraryID()))};
    LibraryRepository lib_rep;
    auto res = lib_rep.query(session, std::shared_ptr<LibarySpecification>(new GetLibrary(lfs)));
    if (res.empty()) {
        Logger::getInstance()->log(1, __FILE__, __LINE__, __TIME__,"no such library!");
        throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                "no such library!");
    }
    BookConverter converter;
    DBBook dbBook = converter.convert(book);
    int id;
    if (session->exec("select id from Book "
                      "where name = :name and author = '" + dbBook.get_author() + "'",
                      dbBook.get_name(),
                      id) != 0)
    {
        session->exec("insert into Book (name, author) "
                      "values('" + dbBook.get_name() + "', '" +
                      dbBook.get_author() + "')");

        session->exec_into("select max(id) "
                      "from Book;", id);
    }
    dbBook.set_book_id(id);
    session->exec_using("insert into BookItem (book_id, lib_id, acc_id) "
                "values(:book_id, :lib_id, NULL)",
                dbBook.get_mapped_book_item());
}
void BookRepository::updateBook(std::shared_ptr<Session> session, std::shared_ptr<Book> book)
{
    std::vector<std::shared_ptr<LibraryFilter>> lfs = {std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(book->getLibraryID()))};
    LibraryRepository lib_rep;
    auto res = lib_rep.query(session, std::shared_ptr<LibarySpecification>(new GetLibrary(lfs)));
    if (res.empty()) {
        Logger::getInstance()->log(1, __FILE__, __LINE__, __TIME__,"no such library!");
        throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                "no such library!");
    }

    BookConverter converter;
    DBBook dbbook = converter.convert(book);
    std::string q = "update Book set name = :name, author = :author "
                    "where id = (select max(Book.id) from Book join Bookitem on book_id = Book.id "
                    "where Bookitem.id = " + std::to_string(book->getID()) + ")";
    session->exec_using(q,
                        dbbook.get_mapped_book());
    q = "update BookItem set lib_id = :lib_id "
        "where id = " + std::to_string(book->getID());
    session->exec_using(q,
                        book->getLibraryID());
}
void BookRepository::removeBook(std::shared_ptr<Session> session, int id)
{
    std::string q = "delete from BookItem "
        "where id = " + std::to_string(id);
    session->exec(q);
}