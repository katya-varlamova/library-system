//
// Created by Екатерина on 21.11.2022.
//

#ifndef SRC_ADMINACCOUNTSOBJECTMOTHER_H
#define SRC_ADMINACCOUNTSOBJECTMOTHER_H

#include "../Logic/Entities/Account/AdminAccount.h"
#include <vector>
class AdminAccountsObjectMother {
public:
    std::vector<AdminAccount> getDefault();
    std::vector<AdminAccount> getWithLogin(std::vector<AdminAccount> accounts,  std::string login);
    std::vector<AdminAccount> getWithID(std::vector<AdminAccount> accounts, int id);
    std::vector<AdminAccount> getWithAdd(std::vector<AdminAccount> accounts, AdminAccount account);
    std::vector<AdminAccount> getWithDel(std::vector<AdminAccount> accounts, int id);
    std::vector<AdminAccount> getWithUpd(std::vector<AdminAccount> accounts, int id, AdminAccount account);
};


#endif //SRC_ADMINACCOUNTSOBJECTMOTHER_H
