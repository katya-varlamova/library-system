//
// Created by Екатерина on 15.05.2022.
//

#ifndef SRC_DELETEREADERACCOUNTCOMMAND_H
#define SRC_DELETEREADERACCOUNTCOMMAND_H

#include "../Command.h"
#include "../../../Entities/DBAccount/ReaderAccount/IReaderAccountRepository.h"
class DeleteReaderAccountCommand: public Command {
public:
    DeleteReaderAccountCommand(std::shared_ptr<IReaderAccountRepository> repository,
                               int id) {
        this->id = id;
        this->repository = repository;
    }

    void execute(std::shared_ptr<Session> session) override {
        session->begin_transaction();
        repository->removeAccount(session, id);
        session->commit_transaction();
    }

private:
    int id;
    std::shared_ptr<IReaderAccountRepository> repository;
};


#endif //SRC_DELETEREADERACCOUNTCOMMAND_H
