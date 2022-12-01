//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_GETADMINACCOUNT_H
#define SRC_GETADMINACCOUNT_H

#include "AdminAccountSpecification.h"
#include "../../AccountFilters/AccountFilter.h"

class GetAdminAccount : public AdminAccountSpecification{
public:
    GetAdminAccount(const std::vector<std::shared_ptr<AccountFilter>> &filters)
    {
        this->filters = filters;
    }
    std::vector<DBAdminAccount> exec(std::shared_ptr<Session<>> session) override;

protected:
    std::vector<std::shared_ptr<AccountFilter>> filters;
};


#endif //SRC_GETADMINACCOUNT_H
