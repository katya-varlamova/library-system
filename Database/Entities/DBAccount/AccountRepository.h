//
// Created by Екатерина on 27.03.2022.
//

#ifndef SRC_ACCOUNTREPOSITORY_H
#define SRC_ACCOUNTREPOSITORY_H


#include <memory>
#include <soci/rowset.h>
#include <libpq-fe.h>
#include <soci/soci.h>
#include "../../../Logic/Entities/Account/Account.h"
#include "AccountSpecifications/AccountSpecification.h"
#include "AccountConverter.h"
class AccountRepository {
public:
    void addAccount(soci::session & session, std::shared_ptr<Account> account);
    void removeAccount(soci::session & session, std::shared_ptr<Account> account);
    void updateAccount(soci::session & session, std::shared_ptr<Account> account);

    std::vector<std::shared_ptr<Account>> query(soci::session & session, std::shared_ptr<AccountSpecification> specification);
};


#endif //SRC_ACCOUNTREPOSITORY_H
