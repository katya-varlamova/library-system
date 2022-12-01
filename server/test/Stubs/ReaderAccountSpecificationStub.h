//
// Created by Екатерина on 23.11.2022.
//

#ifndef SRC_READERACCOUNTSPECIFICATIONSTUB_H
#define SRC_READERACCOUNTSPECIFICATIONSTUB_H
#include "../Database/Entities/DBAccount/ReaderAccount/ReaderAccountSpecifications/ReaderAccountSpecification.h"

class ReaderAccountSpecificationStub : public ReaderAccountSpecification {
public:
    ReaderAccountSpecificationStub() = default;
    virtual std::vector<DBReaderAccount> exec(std::shared_ptr<Session<>> session) {
        session->exec("select ReaderAccount.id, ReaderAccount.acc_id, phone from Account join ReaderAccount on ReaderAccount.acc_id = Account.id where login = 'l1'");
        DBReaderAccount dbAccount;
        return std::vector<DBReaderAccount>({dbAccount});
    }
};
#endif //SRC_READERACCOUNTSPECIFICATIONSTUB_H
