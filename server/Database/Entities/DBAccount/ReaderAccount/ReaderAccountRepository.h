//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_READERACCOUNTREPOSITORY_H
#define SRC_READERACCOUNTREPOSITORY_H


#include "../../../Connection/Session.h"
#include "../../../../Logic/Entities/Account/ReaderAccount.h"
#include "../AccountFilters/ByAccountIDFilter.h"
#include "../AccountSpecifications/GetAccount.h"
#include "../AccountRepository.h"
#include "ReaderAccountConverter.h"
#include "../../../DatabseException.h"
#include "DBReaderAccount.h"
#include "ReaderAccountSpecifications/ReaderAccountSpecification.h"

class ReaderAccountRepository {
public:
    void addAccount(std::shared_ptr<Session> session, std::shared_ptr<ReaderAccount> account);
    void removeAccount(std::shared_ptr<Session> session, int id);
    void updateAccount(std::shared_ptr<Session> session, std::shared_ptr<ReaderAccount> account);

    std::vector<std::shared_ptr<ReaderAccount>> query(std::shared_ptr<Session> session, std::shared_ptr<ReaderAccountSpecification> specification);
};

#endif //SRC_READERACCOUNTREPOSITORY_H
