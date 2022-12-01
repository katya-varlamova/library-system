//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_ADMINACCOUNTREPOSITORY_H
#define SRC_ADMINACCOUNTREPOSITORY_H


#include "../../../Connection/Session.h"
#include "../../../../Logic/Entities/Account/AdminAccount.h"
#include "AdminAccountSpecifications/AdminAccountSpecification.h"
#include "AdminAccountConverter.h"
#include "../AccountRepository.h"
#include "../AccountSpecifications/GetAccount.h"
#include "../AccountFilters/ByAccountIDFilter.h"
#include "IAdminAccountRepository.h"
class AdminAccountRepository : public IAdminAccountRepository{
public:
    void addAccount(const std::shared_ptr<Session<>> &session, std::shared_ptr<AdminAccount> account);
    void removeAccount(const std::shared_ptr<Session<>> &session, int id);
    void updateAccount(const std::shared_ptr<Session<>> &session, std::shared_ptr<AdminAccount> account);

    std::vector<std::shared_ptr<AdminAccount>> query(const std::shared_ptr<Session<>> &session, std::shared_ptr<AdminAccountSpecification> specification);
};


#endif //SRC_ADMINACCOUNTREPOSITORY_H
