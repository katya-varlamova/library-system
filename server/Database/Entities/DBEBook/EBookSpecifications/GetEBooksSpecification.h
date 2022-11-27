//
// Created by Екатерина on 23.05.2022.
//

#ifndef SRC_GETEBOOKSSPECIFICATION_H
#define SRC_GETEBOOKSSPECIFICATION_H
#include "EBookSpecification.h"

class GetEBooksSpecification : public EBookSpecification{
public:
    GetEBooksSpecification(const std::vector<std::shared_ptr<Filter>> &filters)
    {
        this->filters = filters;
    }
    std::vector<DBEBook> exec(std::shared_ptr<Session<>> session) override;

protected:
    std::vector<std::shared_ptr<Filter>> filters;
};


#endif //SRC_GETEBOOKSSPECIFICATION_H
