//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_LIBRARIANACCOUNT_H
#define SRC_LIBRARIANACCOUNT_H

#include <string>
#include "Account.h"
#include "../Library/Library.h"

class LibrarianAccount {
public:
    LibrarianAccount(const std::shared_ptr<Account> &acc, int lib_id)
    {
        this->lib_id = lib_id;
        this->acc = acc;
    }
    std::shared_ptr<Account> getAccount();
    int getLibraryID();
    int getID()
    {
        return id;
    }
    void setID(int id)
    {
        this->id = id;
    }
private:
    int id;
    int lib_id;
    std::shared_ptr<Account> acc;
};


#endif //SRC_LIBRARIANACCOUNT_H
