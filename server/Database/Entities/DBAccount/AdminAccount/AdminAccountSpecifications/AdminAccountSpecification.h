//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_ADMINACCOUNTSPECIFICATION_H
#define SRC_ADMINACCOUNTSPECIFICATION_H
#include "../../../../../Logic/Entities/Account/Account.h"
#include "../DBAdminAccount.h"
#include "../../../../Connection/Session.h"
class AdminAccountSpecification{
public:
    virtual std::vector<DBAdminAccount> exec(std::shared_ptr<Session<>> session) = 0;
};


#endif //SRC_ADMINACCOUNTSPECIFICATION_H
