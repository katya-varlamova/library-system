//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_REGISTERLIBRARIANCOMMAND_H
#define SRC_REGISTERLIBRARIANCOMMAND_H

#include <string>
#include "../Command.h"
#include <soci/session.h>
#include "../../../../Logic/Entities/Account/Account.h"
#include "../../../Entities/DBAccount/AccountRepository.h"
#include "../../../Entities/DBAccount/LibrarianAccount/LibrarianAccountRepository.h"

class RegisterLibrarianCommand : public Command {
public:
    RegisterLibrarianCommand(std::shared_ptr<ILibrarianAccountRepository> repository, const std::shared_ptr<LibrarianAccount> &acc) {
        this->repository = repository;
        this->acc = acc;}
    virtual void execute(std::shared_ptr<Session>  session) override;

private:
    std::shared_ptr<LibrarianAccount> acc;
    std::shared_ptr<ILibrarianAccountRepository> repository;
};
#endif //SRC_REGISTERLIBRARIANCOMMAND_H
