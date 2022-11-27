//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_GETACCOUNT_H
#define SRC_GETACCOUNT_H


#include "AccountSpecification.h"
#include <libpq-fe.h>
#include <soci/soci.h>
#include "../../../Connection/Session.h"
#include "../AccountFilters/AccountFilter.h"

class GetAccount : public AccountSpecification{
public:
    GetAccount(const std::vector<std::shared_ptr<AccountFilter>> &filters)
    {
        this->filters = filters;
    }
    virtual std::vector<DBAccount> exec(std::shared_ptr<Session<>> session) override;

protected:
    std::vector<std::shared_ptr<AccountFilter>> filters;
};


#endif //SRC_GETACCOUNT_H
