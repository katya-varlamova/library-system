//
// Created by Екатерина on 15.05.2022.
//

#ifndef SRC_DELETELIBRARIANACCOUNTCOMMAND_H
#define SRC_DELETELIBRARIANACCOUNTCOMMAND_H


#include "../Command.h"
#include "../../../Entities/DBAccount/LibrarianAccount/LibrarianAccountRepository.h"
class DeleteLibrarianAccountCommand: public Command{
public:
    DeleteLibrarianAccountCommand(int id){ this->id = id;}
    void execute(std::shared_ptr<Session> session) override
    {
        LibrarianAccountRepository repository;
        session->begin_transaction();
        repository.removeAccount(session, id);
        session->commit_transaction();
    }
private:
    int id;
};
#endif //SRC_DELETELIBRARIANACCOUNTCOMMAND_H
