//
// Created by Екатерина on 16.05.2022.
//

#ifndef SRC_IADMINACCOUNTREPOSITORY_H
#define SRC_IADMINACCOUNTREPOSITORY_H
#include "../../../Connection/Session.h"
#include "../../../../Logic/Entities/Account/AdminAccount.h"
#include "AdminAccountSpecifications/AdminAccountSpecification.h"
#include "AdminAccountConverter.h"
#include "../AccountRepository.h"
#include "../AccountSpecifications/GetAccount.h"
#include "../AccountFilters/ByAccountIDFilter.h"
class IAdminAccountRepository {
public:
    virtual void addAccount(const std::shared_ptr<Session<>> &session, std::shared_ptr<AdminAccount> account) = 0;
    virtual void removeAccount(const std::shared_ptr<Session<>> &session, int id) = 0;
    virtual void updateAccount(const std::shared_ptr<Session<>> &session, std::shared_ptr<AdminAccount> account) = 0;

    virtual std::vector<std::shared_ptr<AdminAccount>> query(const std::shared_ptr<Session<>> &session, std::shared_ptr<AdminAccountSpecification> specification) = 0;
};

#endif //SRC_IADMINACCOUNTREPOSITORY_H
