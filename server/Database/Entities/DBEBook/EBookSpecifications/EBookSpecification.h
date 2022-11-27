//
// Created by Екатерина on 23.05.2022.
//

#ifndef SRC_EBOOKSPECIFICATION_H
#define SRC_EBOOKSPECIFICATION_H
#include "../DBEBook.h"
#include "../../../DatabseException.h"
#include "../../../Connection/Session.h"
#include "../../DBBook/BookFilters/BookFilter.h"
#include "../DBEBook.h"
class EBookSpecification
{
public:
    EBookSpecification() = default;
    virtual std::vector<DBEBook> exec(std::shared_ptr<Session<>> session) = 0;
};

#endif //SRC_EBOOKSPECIFICATION_H
