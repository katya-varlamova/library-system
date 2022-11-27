//
// Created by Екатерина on 21.11.2022.
//

#ifndef SRC_ACCOUNTSOBJECTMOTHER_H
#define SRC_ACCOUNTSOBJECTMOTHER_H

#include "../Logic/Entities/Account/Account.h"
#include <vector>
class AccountsObjectMother {
public:
    std::vector<Account> getDefault();
    std::vector<Account> getWithLogin(std::vector<Account> accounts,  std::string login);
    std::vector<Account> getWithID(std::vector<Account> accounts, int id);
    std::vector<Account> getWithAdd(std::vector<Account> accounts, Account account);
    std::vector<Account> getWithDel(std::vector<Account> accounts, int id);
    std::vector<Account> getWithUpd(std::vector<Account> accounts, int id, Account account);
};


#endif //SRC_ACCOUNTSOBJECTMOTHER_H
