//
// Created by Екатерина on 27.03.2022.
//

#ifndef SRC_BOOKREPOSITORY_H
#define SRC_BOOKREPOSITORY_H

#include <soci/rowset.h>
#include "DBBook.h"
#include "../../../Logic/Entities/Book/Book.h"
#include "BookSpecifications/BookSpecification.h"
#include "BookConverter.h"
#include <soci/error.h>
class BookRepository {
public:
    void addBook(soci::session & session, std::shared_ptr<Book> book);
    void removeBook(soci::session & session, std::shared_ptr<Book> book);
    void updateBook(soci::session & session, std::shared_ptr<Book> book);

    std::vector<std::shared_ptr<Book>> query(soci::session & session, std::shared_ptr<BookSpecification> specification);
};


#endif //SRC_BOOKREPOSITORY_H
