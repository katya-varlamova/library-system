//
// Created by Екатерина on 27.03.2022.
//

#ifndef SRC_ACCOUNTSPECIFICATION_H
#define SRC_ACCOUNTSPECIFICATION_H

#include "../../../../Logic/Entities/Account/Account.h"
//#include <soci/session.h>
//#include <libpq-fe.h>
//#include <soci/soci.h>
#include "../DBAccount.h"
class AccountSpecification {
public:
    AccountSpecification() = default;
    virtual std::vector<DBAccount> exec(soci::session & session) = 0;
};


#endif //SRC_ACCOUNTSPECIFICATION_H
