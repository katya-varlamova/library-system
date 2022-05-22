//
// Created by Екатерина on 15.05.2022.
//

#ifndef SRC_DELETELIBRARIANACCOUNTCOMMAND_H
#define SRC_DELETELIBRARIANACCOUNTCOMMAND_H


#include "../Command.h"
#include "../../../Entities/DBAccount/LibrarianAccount/LibrarianAccountRepository.h"
class DeleteLibrarianAccountCommand: public Command{
public:
    DeleteLibrarianAccountCommand(const std::shared_ptr<ILibrarianAccountRepository> &repository, int id)
    {
        this->id = id;
        this->repository = repository;
    }
    void execute(std::shared_ptr<Session> session) override
    {
        session->begin_transaction();
        repository->removeAccount(session, id);
        session->commit_transaction();
    }
private:
    int id;
    std::shared_ptr<ILibrarianAccountRepository> repository;
};
#endif //SRC_DELETELIBRARIANACCOUNTCOMMAND_H
