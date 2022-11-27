
//
// Created by Екатерина on 23.11.2022.
//

#ifndef SRC_ADMINACCOUNTSPECIFICATIONSTUB_H
#define SRC_ADMINACCOUNTSPECIFICATIONSTUB_H
#include "../Database/Entities/DBAccount/AdminAccount/AdminAccountSpecifications/AdminAccountSpecification.h"

class AdminAccountSpecificationStub : public AdminAccountSpecification {
public:
    AdminAccountSpecificationStub() = default;
    virtual std::vector<DBAdminAccount> exec(std::shared_ptr<Session<>> session) {
        session->exec("select AdminAccount.id, AdminAccount.acc_id from Account join AdminAccount on AdminAccount.acc_id = Account.id where login = 'l1'");
        DBAdminAccount dbAccount;
        return std::vector<DBAdminAccount>({dbAccount});
    }
};
#endif //SRC_ADMINACCOUNTSPECIFICATIONSTUB_H
