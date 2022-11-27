//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_READERACCOUNTSPECIFICATION_H
#define SRC_READERACCOUNTSPECIFICATION_H

#include "../DBReaderAccount.h"
#include "../../../../Connection/Session.h"
class ReaderAccountSpecification {
public:
    virtual std::vector<DBReaderAccount> exec(std::shared_ptr<Session<>> session) = 0;
};

#endif //SRC_READERACCOUNTSPECIFICATION_H
