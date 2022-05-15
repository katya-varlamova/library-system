//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_ADMINACCOUNTCONVERTER_H
#define SRC_ADMINACCOUNTCONVERTER_H
#include <memory>
#include "../../../../Logic/Entities/Account/AdminAccount.h"
#include "DBAdminAccount.h"
#include "../AccountConverter.h"
class AdminAccountConverter {
public:
    std::shared_ptr<AdminAccount> convert(std::shared_ptr<Account> account)
    {
        return std::shared_ptr<AdminAccount>(new AdminAccount(account));
    }
    DBAdminAccount convert(int acc_id)
    {
        DBAdminAccount acc;
        acc.acc_id = acc_id;
        return acc;
    }
};
#endif //SRC_ADMINACCOUNTCONVERTER_H
