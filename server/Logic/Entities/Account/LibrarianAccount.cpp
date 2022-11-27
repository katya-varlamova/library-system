//
// Created by Екатерина on 10.05.2022.
//

#include "LibrarianAccount.h"
std::shared_ptr<Account> LibrarianAccount::getAccount() const
{
    return acc;
}
int LibrarianAccount::getLibraryID() const
{
    return lib_id;
}