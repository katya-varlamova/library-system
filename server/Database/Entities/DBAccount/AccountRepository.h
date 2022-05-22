//
// Created by Екатерина on 27.03.2022.
//

#ifndef SRC_ACCOUNTREPOSITORY_H
#define SRC_ACCOUNTREPOSITORY_H


#include <memory>
#include <soci/rowset.h>
#include <libpq-fe.h>
#include <soci/soci.h>
#include "../../Connection/Session.h"
#include "../../../Logic/Entities/Account/Account.h"
#include "AccountSpecifications/AccountSpecification.h"
#include "AccountConverter.h"
#include "../DBBook/BookRepository.h"
#include "IAccountRepository.h"
class AccountRepository : public IAccountRepository{
public:
    int addAccount(std::shared_ptr<Session> session, std::shared_ptr<Account> account);
    void removeAccount(std::shared_ptr<Session> session, int id);
    void updateAccount(std::shared_ptr<Session> session, std::shared_ptr<Account> account);

    std::vector<std::shared_ptr<Account>> query(std::shared_ptr<Session> session, std::shared_ptr<AccountSpecification> specification);
};


#endif //SRC_ACCOUNTREPOSITORY_H
