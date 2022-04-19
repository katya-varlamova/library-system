//
// Created by Екатерина on 09.04.2022.
//

#ifndef SRC_GETACCOUNTBYID_H
#define SRC_GETACCOUNTBYID_H

#include "AccountSpecification.h"
#include <libpq-fe.h>
#include <soci/soci.h>
class GetAccountByID : public AccountSpecification{
public:
    GetAccountByID(int id)
    {
        this->id = id;
    }
    virtual std::vector<DBAccount> exec(soci::session & session) override;

private:
    int id;
};


#endif //SRC_GETACCOUNTBYID_H
