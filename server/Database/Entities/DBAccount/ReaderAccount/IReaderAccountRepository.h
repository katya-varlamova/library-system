//
// Created by Екатерина on 16.05.2022.
//

#ifndef SRC_IREADERACCOUNTREPOSITORY_H
#define SRC_IREADERACCOUNTREPOSITORY_H
#include "../../../Connection/Session.h"
#include "../../../../Logic/Entities/Account/ReaderAccount.h"
#include "../AccountFilters/ByAccountIDFilter.h"
#include "../AccountSpecifications/GetAccount.h"
#include "../AccountRepository.h"
#include "ReaderAccountConverter.h"
#include "../../../DatabseException.h"
#include "DBReaderAccount.h"
#include "ReaderAccountSpecifications/ReaderAccountSpecification.h"
class IReaderAccountRepository {
public:
    virtual void addAccount(std::shared_ptr<Session<>> session, std::shared_ptr<ReaderAccount> account) = 0;
    virtual void removeAccount(std::shared_ptr<Session<>> session, int id) = 0;
    virtual void updateAccount(std::shared_ptr<Session<>> session, std::shared_ptr<ReaderAccount> account) = 0;

    virtual std::vector<std::shared_ptr<ReaderAccount>> query(std::shared_ptr<Session<>> session, std::shared_ptr<ReaderAccountSpecification> specification) = 0;
};
#endif //SRC_IREADERACCOUNTREPOSITORY_H
