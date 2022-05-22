//
// Created by Екатерина on 16.05.2022.
//

#ifndef SRC_IBOOKREPOSITORY_H
#define SRC_IBOOKREPOSITORY_H
#include <soci/rowset.h>
#include "DBBook.h"
#include "../../../Logic/Entities/Book/Book.h"
#include "BookSpecifications/BookSpecification.h"
#include "../DBLibrary/LibraryRepository.h"
#include "../DBLibrary/LibraryFilters/ByLibraryIDFilter.h"
#include "BookConverter.h"
#include <soci/error.h>
class IBookRepository {
public:
    virtual void addBook(std::shared_ptr<Session> session, std::shared_ptr<Book> book) = 0;
    virtual void removeBook(std::shared_ptr<Session> session, int id) = 0;
    virtual void updateBook(std::shared_ptr<Session> session, std::shared_ptr<Book> book) = 0;

    virtual std::vector<std::shared_ptr<Book>> query(std::shared_ptr<Session> session, std::shared_ptr<BookSpecification> specification) = 0;
};
#endif //SRC_IBOOKREPOSITORY_H
