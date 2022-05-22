//
// Created by Екатерина on 23.05.2022.
//

#include "EBookRepository.h"
#include "../../../Logger/Logger.h"

std::vector<std::shared_ptr<EBook>> EBookRepository::query(std::shared_ptr<Session> session, std::shared_ptr<EBookSpecification> specification)
{
    std::vector<DBEBook> dbb = specification->exec(session);
    std::vector<std::shared_ptr<EBook>> vec;
    EBookConverter converter;
    for (auto &i : dbb) {
        vec.push_back(converter.convert(i));
    }
    return vec;
}
void EBookRepository::addBook(std::shared_ptr<Session> session, std::shared_ptr<EBook> book)
{
    EBookConverter converter;
    DBEBook dbBook = converter.convert(book);
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
    session->exec_using("insert into EBook (book_id, link) "
                        "values(:book_id, :link)",
                        dbBook.get_mapped_ebook());
}
void EBookRepository::updateBook(std::shared_ptr<Session> session, std::shared_ptr<EBook> book)
{
    EBookConverter converter;
    DBEBook dbbook = converter.convert(book);
    std::string q = "update Book set name = :name, author = :author "
                    "where id = (select max(Book.id) from Book join EBook on book_id = Book.id "
                    "where Ebook.id = " + std::to_string(book->getID()) + ")";
    session->exec_using(q,
                        dbbook.get_mapped_book());
    q = "update EBook set link = :link "
        "where id = " + std::to_string(book->getID());
    session->exec_using(q,
                        book->getLink());
}
void EBookRepository::removeBook(std::shared_ptr<Session> session, int id)
{
    std::string q = "delete from EBook "
                    "where id = " + std::to_string(id);
    session->exec(q);
}