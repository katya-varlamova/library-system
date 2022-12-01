//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_GETREADERACCOUNT_H
#define SRC_GETREADERACCOUNT_H

#include "ReaderAccountSpecification.h"
#include "../../AccountFilters/AccountFilter.h"

class GetReaderAccount : public ReaderAccountSpecification {
public:
    GetReaderAccount(const std::vector<std::shared_ptr<AccountFilter>> &filters)
    {
        this->filters = filters;
    }
    std::vector<DBReaderAccount> exec(std::shared_ptr<Session<>> session) override;

protected:
    std::vector<std::shared_ptr<AccountFilter>> filters;
};


#endif //SRC_GETREADERACCOUNT_H
