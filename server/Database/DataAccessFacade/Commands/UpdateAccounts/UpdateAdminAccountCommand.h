//
// Created by Екатерина on 11.05.2022.
//

#ifndef SRC_UPDATEADMINACCOUNTCOMMAND_H
#define SRC_UPDATEADMINACCOUNTCOMMAND_H
#include "../Command.h"
#include "../../../Entities/DBAccount/AdminAccount/AdminAccountRepository.h"
class UpdateAdminAccountCommand: public Command{
public:
    UpdateAdminAccountCommand(std::shared_ptr<IAdminAccountRepository> repository, const std::shared_ptr<AdminAccount> &acc){
        this->repository = repository;this->acc = acc;}
    void execute(std::shared_ptr<Session> session) override
    {
        session->begin_transaction();
        repository->updateAccount(session, acc);
        session->commit_transaction();
    }

private:
    std::shared_ptr<IAdminAccountRepository> repository;
    std::shared_ptr<AdminAccount> acc;
};
#endif //SRC_UPDATEADMINACCOUNTCOMMAND_H
