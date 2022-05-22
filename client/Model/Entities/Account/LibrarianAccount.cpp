//
// Created by Екатерина on 10.05.2022.
//

#include "LibrarianAccount.h"
std::shared_ptr<Account> LibrarianAccount::getAccount()
{
    return acc;
}
int LibrarianAccount::getLibraryID()
{
    return lib_id;
}