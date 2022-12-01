//
// Created by Екатерина on 23.05.2022.
//

#ifndef SRC_IEBOOKREPOSITORY_H
#define SRC_IEBOOKREPOSITORY_H


#include "DBEBook.h"
#include "../../../Logic/Entities/EBook/EBook.h"
#include "EBookSpecifications/EBookSpecification.h"
#include "EBookConverter.h"

class IEBookRepository {
public:
    virtual void addBook(std::shared_ptr<Session<>> session, std::shared_ptr<EBook> book) = 0;
    virtual void removeBook(std::shared_ptr<Session<>> session, int id) = 0;
    virtual void updateBook(std::shared_ptr<Session<>> session, std::shared_ptr<EBook> book) = 0;

    virtual std::vector<std::shared_ptr<EBook>> query(std::shared_ptr<Session<>> session, std::shared_ptr<EBookSpecification> specification) = 0;
};

#endif //SRC_IEBOOKREPOSITORY_H
