//
// Created by Екатерина on 23.05.2022.
//

#include "EBookRepository.h"
#include "../../../Logger/Logger.h"

std::vector<std::shared_ptr<EBook>> EBookRepository::query(std::shared_ptr<Session<>> session, std::shared_ptr<EBookSpecification> specification)
{
    std::vector<DBEBook> dbb = specification->exec(session);
    std::vector<std::shared_ptr<EBook>> vec;
    EBookConverter converter;
    for (auto &i : dbb) {
        vec.push_back(converter.convert(i));
    }
    return vec;
}
void EBookRepository::addBook(std::shared_ptr<Session<>> session, std::shared_ptr<EBook> book)
{
    EBookConverter converter;
    DBEBook dbBook = converter.convert(book);
    int id;
    if (session->exec_into("select id from Book "
                      "where name = '" + dbBook.get_name() + "' and author = '" + dbBook.get_author() + "'",
                      id) != 0)
    {
        session->exec("insert into Book (name, author) "
                      "values('" + dbBook.get_name() + "', '" +
                      dbBook.get_author() + "')");

        session->exec_into("select max(id) "
                           "from Book;", id);
    }
    dbBook.set_book_id(id);
    session->exec("insert into EBook (book_id, link) "
                        "values(" + std::to_string(dbBook.get_mapped_ebook().book_id) + ", '" + dbBook.get_mapped_ebook().link + "')");
}
void EBookRepository::updateBook(std::shared_ptr<Session<>> session, std::shared_ptr<EBook> book)
{
    EBookConverter converter;
    DBEBook dbbook = converter.convert(book);
    std::string q = "update Book set name = '" + dbbook.get_mapped_book().name + "', author = '" + dbbook.get_mapped_book().author + "' "
                    "where id = (select max(Book.id) from Book join EBook on book_id = Book.id "
                    "where Ebook.id = " + std::to_string(book->getID()) + ")";
    session->exec(q);
    q = "update EBook set link = '" + book->getLink() + "' "
        "where id = " + std::to_string(book->getID());
    session->exec(q);
}
void EBookRepository::removeBook(std::shared_ptr<Session<>> session, int id)
{
    std::string q = "delete from EBook "
                    "where id = " + std::to_string(id);
    session->exec(q);
}