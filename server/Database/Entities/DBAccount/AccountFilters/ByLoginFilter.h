//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_BYLOGINFILTER_H
#define SRC_BYLOGINFILTER_H
#include "AccountFilter.h"
class ByLoginFilter : public AccountFilter{
public:
    ByLoginFilter(const std::string &login)
    {
        this->login = login;
    }
    std::string getEqualClause() override
    {
        return "login = '" + login + "'";
    }
private:
    std::string login;
};

#endif //SRC_BYLOGINFILTER_H
