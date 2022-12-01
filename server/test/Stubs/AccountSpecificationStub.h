//
// Created by Екатерина on 21.11.2022.
//

#ifndef SRC_ACCOUNTSPECIFICATIONSTUB_H
#define SRC_ACCOUNTSPECIFICATIONSTUB_H
#include "../Database/Entities/DBAccount/AccountSpecifications/AccountSpecification.h"

class AccountSpecificationStub : public AccountSpecification {
public:
    AccountSpecificationStub() = default;
    virtual std::vector<DBAccount> exec(std::shared_ptr<Session<>> session) {
        session->exec("select * from Account where login = 'l1'");
        DBAccount dbAccount;
        dbAccount.login = "";
        return std::vector<DBAccount>({dbAccount});
    }
};
#endif //SRC_ACCOUNTSPECIFICATIONSTUB_H
