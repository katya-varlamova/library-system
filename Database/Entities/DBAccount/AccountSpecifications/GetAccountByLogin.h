//
// Created by Екатерина on 03.04.2022.
//

#ifndef SRC_GETACCOUNTBYLOGIN_H
#define SRC_GETACCOUNTBYLOGIN_H
#include "AccountSpecification.h"
#include "../DBAccount.h"
#include <libpq-fe.h>
#include <soci/soci.h>
class GetAccountByLogin : public AccountSpecification
{
public:
    GetAccountByLogin(std::string login)
    {
        this->login = login;
    }
    virtual std::vector<DBAccount> exec(soci::session & session) override;

private:
    std::string login;
};

#endif //SRC_GETACCOUNTBYLOGIN_H
