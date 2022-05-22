//
// Created by Екатерина on 11.05.2022.
//

#ifndef SRC_UPDATELIBRARIANACCOUNTCOMMAND_H
#define SRC_UPDATELIBRARIANACCOUNTCOMMAND_H
#include "../Command.h"
#include "../../../Entities/DBAccount/LibrarianAccount/LibrarianAccountRepository.h"
class UpdateLibrarianAccountCommand: public Command{
public:
    UpdateLibrarianAccountCommand(std::shared_ptr<ILibrarianAccountRepository> repository, const std::shared_ptr<LibrarianAccount> &acc){
        this->repository = repository;
        this->acc = acc;}
    void execute(std::shared_ptr<Session> session) override
    {
        session->begin_transaction();
        repository->updateAccount(session, acc);
        session->commit_transaction();
    }

private:
    std::shared_ptr<ILibrarianAccountRepository> repository;
    std::shared_ptr<LibrarianAccount> acc;
};
#endif //SRC_UPDATELIBRARIANACCOUNTCOMMAND_H
