//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_ADMINACCOUNT_H
#define SRC_ADMINACCOUNT_H


#include "Account.h"

class AdminAccount {
public:
    AdminAccount(const std::shared_ptr<Account> &acc)
    {
        this->acc = acc;
    }
    std::shared_ptr<Account> getAccount();
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
    std::shared_ptr<Account> acc;
};


#endif //SRC_ADMINACCOUNT_H
