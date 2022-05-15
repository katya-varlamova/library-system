//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_READERACCOUNTCONVERTER_H
#define SRC_READERACCOUNTCONVERTER_H
#include "../../../../Logic/Entities/Account/ReaderAccount.h"
#include "DBReaderAccount.h"
class ReaderAccountConverter {
public:
    std::shared_ptr<ReaderAccount> convert(std::shared_ptr<Account> account, DBReaderAccount dacc)
    {
        return std::shared_ptr<ReaderAccount>(new ReaderAccount(account, dacc.phone));
    }
    DBReaderAccount convert(std::shared_ptr<ReaderAccount> racc, int acc_id)
    {
        DBReaderAccount acc;
        acc.acc_id = acc_id;
        acc.phone = racc->getPhone();
        return acc;
    }
};

#endif //SRC_READERACCOUNTCONVERTER_H
