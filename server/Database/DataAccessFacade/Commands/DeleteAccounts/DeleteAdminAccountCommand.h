//
// Created by Екатерина on 15.05.2022.
//

#ifndef SRC_DELETEADMINACCOUNTCOMMAND_H
#define SRC_DELETEADMINACCOUNTCOMMAND_H


#include "../Command.h"
#include "../../../Entities/DBAccount/AdminAccount/AdminAccountRepository.h"
#include "../../../../Logger/Logger.h"

class DeleteAdminAccountCommand: public Command{
public:
    DeleteAdminAccountCommand(std::shared_ptr<IAdminAccountRepository> repository, int id){
        this->repository = repository;
        this->id = id;
    }
    void execute(std::shared_ptr<Session> session) override
    {
        session->begin_transaction();
        repository->removeAccount(session, id);
        session->commit_transaction();
        Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"admin account deleted!");
    }

private:
    int id;
    std::shared_ptr<IAdminAccountRepository> repository;
};

#endif //SRC_DELETEADMINACCOUNTCOMMAND_H
