//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_REGISTERREADERCOMMAND_H
#define SRC_REGISTERREADERCOMMAND_H

#include <string>
#include "../../../../DataAccessFacade/Commands/Command.h"
#include <soci/session.h>
#include "../../../../../Logic/Entities/Account/Account.h"
#include "../../../../Entities/DBAccount/AccountRepository.h"
#include "../../../../Entities/DBAccount/ReaderAccount/IReaderAccountRepository.h"

class RegisterReaderCommand : public Command {
public:
    RegisterReaderCommand(std::shared_ptr<IReaderAccountRepository> repository, const std::shared_ptr<ReaderAccount> &acc) {
        this->repository = repository;this->acc = acc;}
    virtual void execute(std::shared_ptr<Session<>>  session) override;

private:
    std::shared_ptr<IReaderAccountRepository> repository;
    std::shared_ptr<ReaderAccount> acc;
};



#endif //SRC_REGISTERREADERCOMMAND_H
