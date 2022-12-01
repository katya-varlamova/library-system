//
// Created by Екатерина on 23.11.2022.
//

#ifndef SRC_READERACCOUNTSOBJECTMOTHER_H
#define SRC_READERACCOUNTSOBJECTMOTHER_H

#include "../Logic/Entities/Account/ReaderAccount.h"
#include <vector>
class ReaderAccountsObjectMother {
public:
    std::vector<ReaderAccount> getDefault();
    std::vector<ReaderAccount> getWithLogin(std::vector<ReaderAccount> accounts,  std::string login);
    std::vector<ReaderAccount> getWithID(std::vector<ReaderAccount> accounts, int id);
    std::vector<ReaderAccount> getWithAdd(std::vector<ReaderAccount> accounts, ReaderAccount account);
    std::vector<ReaderAccount> getWithDel(std::vector<ReaderAccount> accounts, int id);
    std::vector<ReaderAccount> getWithUpd(std::vector<ReaderAccount> accounts, int id, ReaderAccount account);
};


#endif //SRC_READERACCOUNTSOBJECTMOTHER_H
