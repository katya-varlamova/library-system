//
// Created by Екатерина on 27.03.2022.
//

#include "BookRepository.h"

std::vector<std::shared_ptr<Book>> BookRepository::query(std::shared_ptr<Session> session, std::shared_ptr<BookSpecification> specification)
{
    std::vector<DBBook> dbb = specification->exec(session);
    std::vector<std::shared_ptr<Book>> vec;
    BookConverter converter;
    LibraryRepository lib_rep;
    std::vector<std::shared_ptr<LibraryFilter>> lfs;

    for (auto &i : dbb) {
        lfs = {std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(i.get_lib_id()))};
        auto res = lib_rep.query(session, std::shared_ptr<LibarySpecification>(new GetLibrary(lfs)));
        if (!res.empty())
            vec.push_back(converter.convert(i, res[0]));
    }
    return vec;
}
void BookRepository::addBook(std::shared_ptr<Session> session, std::shared_ptr<Book> book)
{
    BookConverter converter;
    LibraryRepository lib_rep;
    lib_rep.addLibrary(session, book->getLibrary());
    DBBook dbBook = converter.convert(book);
    int id;
    if (session->exec("select id from public.Book "
                      "where name = :name and author = '" + dbBook.get_author() + "'",
                      dbBook.get_name(),
                      id) != 0)
    {
        session->exec("insert into public.Book "
                      "values(default, '" + dbBook.get_name() + "', '" +
                      dbBook.get_author() + "')");

        session->exec_into("select max(id) "
                      "from public.Book;", id);
    }
    dbBook.set_book_id(id);
    session->exec_using("insert into public.BookItem "
                "values(default, :book_id, :lib_id, NULL)",
                dbBook.get_mapped_book_item());
}
void BookRepository::updateBook(std::shared_ptr<Session> session, std::shared_ptr<Book> book)
{
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
                        book->getLibrary()->getID());
}
void BookRepository::removeBook(std::shared_ptr<Session> session, int id)
{
    std::string q = "delete from BookItem "
        "where id = " + std::to_string(id);
    session->exec(q);
}