//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_READERACCOUNT_H
#define SRC_READERACCOUNT_H


#include <string>
#include "Account.h"
#include <memory>
class ReaderAccount {
public:
    ReaderAccount(const std::shared_ptr<Account> &acc, const std::string &phone)
    {
        this->acc = acc;
        this->phone = phone;
    }
    std::shared_ptr<Account> getAccount() const
    {
        return acc;
    }
    std::string getPhone() const
    {
        return phone;
    }
    int getID() const
    {
        return id;
    }
    void setID(int id)
    {
        this->id = id;
    }
    bool operator == (const ReaderAccount &l) const
    {
        return l.getID() == this->getID() &&
               *l.getAccount() == *this->getAccount() &&
               l.getPhone() == this->getPhone();
    }
private:
    int id;
    std::string phone;
    std::shared_ptr<Account> acc;
};


#endif //SRC_READERACCOUNT_H
