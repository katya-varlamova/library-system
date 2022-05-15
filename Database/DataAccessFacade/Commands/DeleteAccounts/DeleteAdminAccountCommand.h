//
// Created by Екатерина on 15.05.2022.
//

#ifndef SRC_DELETEADMINACCOUNTCOMMAND_H
#define SRC_DELETEADMINACCOUNTCOMMAND_H


#include "../Command.h"
#include "../../../Entities/DBAccount/AdminAccount/AdminAccountRepository.h"
class DeleteAdminAccountCommand: public Command{
public:
    DeleteAdminAccountCommand(int id){ this->id = id;}
    void execute(std::shared_ptr<Session> session) override
    {
        AdminAccountRepository repository;
        session->begin_transaction();
        repository.removeAccount(session, id);
        session->commit_transaction();
    }

private:
    int id;
};

#endif //SRC_DELETEADMINACCOUNTCOMMAND_H
