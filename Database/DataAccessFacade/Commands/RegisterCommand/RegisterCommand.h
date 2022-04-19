//
// Created by Екатерина on 04.04.2022.
//

#ifndef SRC_REGISTERCOMMAND_H
#define SRC_REGISTERCOMMAND_H


#include <string>
#include "../Command.h"
#include <soci/session.h>
#include "../../../../Logic/Entities/Account/Account.h"
#include "../../../Entities/DBAccount/AccountRepository.h"
#include "../../../Entities/DBAccount/AccountSpecifications/GetAccountByLogin.h"
class RegisterCommand : public Command {
public:
    RegisterCommand(const std::shared_ptr<Account> &acc) { this->acc = acc;}
    virtual void execute(soci::session & session) override;

private:
    std::shared_ptr<Account> acc;
};


#endif //SRC_REGISTERCOMMAND_H
