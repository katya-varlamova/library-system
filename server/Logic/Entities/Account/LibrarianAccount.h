//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_LIBRARIANACCOUNT_H
#define SRC_LIBRARIANACCOUNT_H

#include <string>
#include "Account.h"
#include "../Library/Library.h"
#include <memory>
class LibrarianAccount {
public:
    LibrarianAccount(const std::shared_ptr<Account> &acc, int lib_id)
    {
        this->lib_id = lib_id;
        this->acc = acc;
    }
    std::shared_ptr<Account> getAccount() const;
    int getLibraryID() const ;
    int getID() const
    {
        return id;
    }
    void setID(int id)
    {
        this->id = id;
    }
    bool operator == (const LibrarianAccount &l) const
    {
        return l.getID() == this->getID() &&
                *l.getAccount() == *this->getAccount() &&
               l.getLibraryID() == this->getLibraryID();
    }
private:
    int id;
    int lib_id;
    std::shared_ptr<Account> acc;
};


#endif //SRC_LIBRARIANACCOUNT_H
