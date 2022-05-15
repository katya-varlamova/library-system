//
// Created by Екатерина on 04.04.2022.
//

#ifndef SRC_ACCOUNTCONVERTER_H
#define SRC_ACCOUNTCONVERTER_H

#include <memory>
#include "../../../Logic/Entities/Account/Account.h"
#include "DBAccount.h"

class AccountConverter {
public:
    std::shared_ptr<Account> convert(DBAccount account)
    {
        std::shared_ptr<Account> acc = std::shared_ptr<Account>(new Account(account.login, account.password, account.role, account.name));
        acc->setID(account.id);
        return acc;
    }
    DBAccount convert(std::shared_ptr<Account> account)
    {
        DBAccount acc;
        acc.name = account->getName();
        acc.role = account->getRole();
        acc.password = account->getPassword();
        acc.login = account->getLogin();
        return acc;
    }
};


#endif //SRC_ACCOUNTCONVERTER_H
