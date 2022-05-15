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
#include "../../../Connection/Session.h"
class AccountSpecification {
public:
    virtual std::vector<DBAccount> exec(std::shared_ptr<Session> session) = 0;
};


#endif //SRC_ACCOUNTSPECIFICATION_H
