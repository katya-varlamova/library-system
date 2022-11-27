//
// Created by Екатерина on 10.05.2022.
//

#include "AdminAccount.h"
std::shared_ptr<Account> AdminAccount::getAccount() const
{
    return acc;
}