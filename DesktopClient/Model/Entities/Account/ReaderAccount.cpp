//
// Created by Екатерина on 10.05.2022.
//

#include "ReaderAccount.h"

std::shared_ptr<Account> ReaderAccount::getAccount()
{
    return acc;
}
std::string ReaderAccount::getPhone()
{
    return phone;
}