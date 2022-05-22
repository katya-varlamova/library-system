//
// Created by Екатерина on 23.05.2022.
//

#ifndef SRC_EBOOKCONVERTER_H
#define SRC_EBOOKCONVERTER_H
#include <memory>
#include "../../../Logic/Entities/EBook/EBook.h"
#include "DBEBook.h"

class EBookConverter {
public:
    std::shared_ptr<EBook> convert(DBEBook book)
    {
        std::shared_ptr<EBook> b = std::shared_ptr<EBook> (new EBook(book.get_name(), book.get_author(), book.get_link()));
        b->setID(book.get_mapped_ebook().id);
        return b;
    }
    DBEBook convert(std::shared_ptr<EBook> &book)
    {
        DBEBook b;
        b.set_name(book->getName());
        b.set_author(book->getAuthor());
        b.set_link(book->getLink());
        b.set_ebook_id(book->getID());
        return b;
    }
};
#endif //SRC_EBOOKCONVERTER_H
