//
// Created by Екатерина on 11.05.2022.
//

#ifndef SRC_UPDATEADMINACCOUNTCOMMAND_H
#define SRC_UPDATEADMINACCOUNTCOMMAND_H
#include "DataAccessFacade/Commands/Command.h"
#include "Entities/DBAccount/AdminAccount/AdminAccountRepository.h"
class UpdateAdminAccountCommand: public Command{
public:
    UpdateAdminAccountCommand(std::shared_ptr<IAdminAccountRepository> repository, std::shared_ptr<IAccountRepository> acc_repository, const std::shared_ptr<AdminAccount> &acc){
        this->repository = repository;
        this->acc = acc;
        this->acc_repository = acc_repository;
    }
    void execute(std::shared_ptr<Session<>> session) override
    {
        session->begin_transaction();
        std::vector<std::shared_ptr<AccountFilter>> fs = {std::shared_ptr<AccountFilter>(new ByAccountIDFilter(acc->getAccount()->getID()))};
        auto res = acc_repository->query(session, std::shared_ptr<AccountSpecification>(new GetAccount(fs)));
        if (res.empty()) {
            throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                    "no such account!");
        }
        repository->updateAccount(session, acc);
        session->commit_transaction();
        Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"admin account was updated!");
    }

private:
    std::shared_ptr<IAdminAccountRepository> repository;
    std::shared_ptr<IAccountRepository> acc_repository;
    std::shared_ptr<AdminAccount> acc;
};
#endif //SRC_UPDATEADMINACCOUNTCOMMAND_H
