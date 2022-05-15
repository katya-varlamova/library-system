//
// Created by Екатерина on 29.03.2022.
//

#ifndef SRC_AUTHCOMMAND_H
#define SRC_AUTHCOMMAND_H

#include <string>
#include "../Command.h"
#include <soci/session.h>
#include "../../../Entities/DBAccount/AccountFilters/ByLoginFilter.h"
#include "../../../../Logic/Entities/Account/Account.h"
#include "../../../Entities/DBAccount/AccountRepository.h"
#include "../../../Entities/DBAccount/AccountSpecifications/GetAccount.h"
class AuthCommand : public Command {
public:
    AuthCommand(std::string login, std::vector<std::shared_ptr<Account>> &acc) : acc(acc) {
        this->login = login;
    }
    virtual void execute(std::shared_ptr<Session> session) override;

private:
    std::string login;
    std::vector<std::shared_ptr<Account>> &acc;
};


#endif //SRC_AUTHCOMMAND_H
