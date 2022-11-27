//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_GETLIBRARIANACCOUNT_H
#define SRC_GETLIBRARIANACCOUNT_H

#include "LibrarianAccountSpecification.h"
#include "../../AccountFilters/AccountFilter.h"

class GetLibrarianAccount : public LibrarianAccountSpecification{
public:
    GetLibrarianAccount(const std::vector<std::shared_ptr<AccountFilter>> &filters)
    {
        this->filters = filters;
    }
    std::vector<DBLibrarianAccount> exec(std::shared_ptr<Session<>> session) override;

protected:
    std::vector<std::shared_ptr<AccountFilter>> filters;
};


#endif //SRC_GETLIBRARIANACCOUNT_H
