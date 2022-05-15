//
// Created by Екатерина on 09.04.2022.
//

#ifndef SRC_BOOKCONVERTER_H
#define SRC_BOOKCONVERTER_H

#include <memory>
#include "../../../Logic/Entities/Book/Book.h"
#include "DBBook.h"

class BookConverter {
public:
    std::shared_ptr<Book> convert(DBBook book, std::shared_ptr<Library> lib)
    {
        std::shared_ptr<Book> b = std::shared_ptr<Book> (new Book(book.get_name(), book.get_author(), lib));
        b->setID(book.get_mapped_book_item().id);
        return b;
    }
    DBBook convert(std::shared_ptr<Book> &book)
    {
        DBBook b;
        b.set_name(book->getName());
        b.set_author(book->getAuthor());
        b.set_lib_id(book->getLibrary()->getID());
        b.set_item_id(book->getID());
        return b;
    }
};


#endif //SRC_BOOKCONVERTER_H
