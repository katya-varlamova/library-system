//
// Created by Екатерина on 27.03.2022.
//

#ifndef SRC_BOOKREPOSITORY_H
#define SRC_BOOKREPOSITORY_H

#include <soci/rowset.h>
#include "DBBook.h"
#include "../../../Logic/Entities/Book/Book.h"
#include "BookSpecifications/BookSpecification.h"
#include "../DBLibrary/LibraryRepository.h"
#include "../DBLibrary/LibraryFilters/ByLibraryIDFilter.h"
#include "BookConverter.h"
#include <soci/error.h>
class BookRepository {
public:
    void addBook(std::shared_ptr<Session> session, std::shared_ptr<Book> book);
    void removeBook(std::shared_ptr<Session> session, int id);
    void updateBook(std::shared_ptr<Session> session, std::shared_ptr<Book> book);

    std::vector<std::shared_ptr<Book>> query(std::shared_ptr<Session> session, std::shared_ptr<BookSpecification> specification);
};


#endif //SRC_BOOKREPOSITORY_H
