//
// Created by Екатерина on 27.03.2022.
//

#include "BookRepository.h"
#include "../DBLibrary/LibraryRepository.h"
#include "../DBLibrary/LibrarySpecifications/GetLibraryByID.h"

std::vector<std::shared_ptr<Book>> BookRepository::query(soci::session & session, std::shared_ptr<BookSpecification> specification)
{
    std::vector<DBBook> dbb = specification->exec(session);
    std::vector<std::shared_ptr<Book>> vec;
    BookConverter converter;
    LibraryRepository lib_rep;

    for (auto &i : dbb) {
        auto res = lib_rep.query(session, std::shared_ptr<LibarySpecification>(new GetLibraryByID(i.get_lib_id())));
        if (!res.empty())
            vec.push_back(converter.convert(i, res[0]));
    }
    return vec;
}
void BookRepository::addBook(soci::session &session, std::shared_ptr<Book> book)
{
    BookConverter converter;
    LibraryRepository lib_rep;
    lib_rep.addLibrary(session, book->getLibrary());
    DBBook dbBook = converter.convert(book);
    soci::indicator ind;
    int id;
    session <<  "select id from public.Book "
                "where name = :name and author = :author",
                soci::into(id, ind),
                soci::use(dbBook.get_name()),
                soci::use(dbBook.get_author());
    if (ind != soci::i_ok)
    {
        session <<  "insert into public.Book "
                    "values(default, :name, :author)",
                    soci::use(dbBook.get_name()),
                    soci::use(dbBook.get_author());;

        session << "select max(id) "
                   "from public.Book;", soci::into(id);
    }
    dbBook.set_book_id(id);
    session <<  "insert into public.BookItem "
                "values(default, :book_id, :lib_id, NULL)",
                soci::use(dbBook.get_mapped_book_item());
}