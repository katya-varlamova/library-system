//
// Created by Екатерина on 04.04.2022.
//

#ifndef SRC_REGISTERADMINCOMMAND_H
#define SRC_REGISTERADMINCOMMAND_H


#include <string>
#include "../Command.h"
#include <soci/session.h>
#include "../../../../Logic/Entities/Account/Account.h"
#include "../../../Entities/DBAccount/AccountRepository.h"
#include "../../../Entities/DBAccount/AdminAccount/AdminAccountRepository.h"

class RegisterAdminCommand : public Command {
public:
    RegisterAdminCommand(std::shared_ptr<IAdminAccountRepository> repository, const std::shared_ptr<AdminAccount> &acc) {
        this->repository = repository;
        this->acc = acc;}
    virtual void execute(std::shared_ptr<Session>  session) override;

private:
    std::shared_ptr<AdminAccount> acc;
    std::shared_ptr<IAdminAccountRepository> repository;
};


#endif //SRC_REGISTERADMINCOMMAND_H
