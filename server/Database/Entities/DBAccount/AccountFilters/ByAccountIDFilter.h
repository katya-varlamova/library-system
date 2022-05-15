//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_BYACCOUNTIDFILTER_H
#define SRC_BYACCOUNTIDFILTER_H
#include "AccountFilter.h"
class ByAccountIDFilter : public AccountFilter{
public:
    ByAccountIDFilter(int id)
    {
        this->id = id;
    }
    std::string getEqualClause() override
    {
        return "Account.id = " + std::to_string(id);
    }
private:
    int id;
};

#endif //SRC_BYACCOUNTIDFILTER_H
