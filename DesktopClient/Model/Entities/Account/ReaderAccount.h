//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_READERACCOUNT_H
#define SRC_READERACCOUNT_H


#include <string>
#include "Account.h"

class ReaderAccount {
public:
    ReaderAccount(const std::shared_ptr<Account> &acc, const std::string &phone)
    {
        this->acc = acc;
        this->phone = phone;
    }
    std::shared_ptr<Account> getAccount();
    std::string getPhone();
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
    std::string phone;
    std::shared_ptr<Account> acc;
};


#endif //SRC_READERACCOUNT_H
