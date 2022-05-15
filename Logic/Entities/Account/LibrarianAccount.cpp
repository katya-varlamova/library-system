//
// Created by Екатерина on 10.05.2022.
//

#include "LibrarianAccount.h"
std::shared_ptr<Account> LibrarianAccount::getAccount()
{
    return acc;
}
std::shared_ptr<Library> LibrarianAccount::getLibrary()
{
    return lib;
}