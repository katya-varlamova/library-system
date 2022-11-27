//
// Created by Екатерина on 23.11.2022.
//

#ifndef SRC_LIBRARIANACCOUNTSOBJECTMOTHER_H
#define SRC_LIBRARIANACCOUNTSOBJECTMOTHER_H
#include "../Logic/Entities/Account/LibrarianAccount.h"
#include <vector>

class LibrarianAccountsObjectMother {
public:
    std::vector<LibrarianAccount> getDefault();
    std::vector<LibrarianAccount> getWithLogin(std::vector<LibrarianAccount> accounts,  std::string login);
    std::vector<LibrarianAccount> getWithID(std::vector<LibrarianAccount> accounts, int id);
    std::vector<LibrarianAccount> getWithAdd(std::vector<LibrarianAccount> accounts, LibrarianAccount account);
    std::vector<LibrarianAccount> getWithDel(std::vector<LibrarianAccount> accounts, int id);
    std::vector<LibrarianAccount> getWithUpd(std::vector<LibrarianAccount> accounts, int id, LibrarianAccount account);
};

#endif //SRC_LIBRARIANACCOUNTSOBJECTMOTHER_H
