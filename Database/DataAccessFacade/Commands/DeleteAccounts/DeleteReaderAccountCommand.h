//
// Created by Екатерина on 15.05.2022.
//

#ifndef SRC_DELETEREADERACCOUNTCOMMAND_H
#define SRC_DELETEREADERACCOUNTCOMMAND_H

#include "../Command.h"
#include "../../../Entities/DBAccount/ReaderAccount/ReaderAccountRepository.h"
class DeleteReaderAccountCommand: public Command {
public:
    DeleteReaderAccountCommand(int id) { this->id = id; }

    void execute(std::shared_ptr<Session> session) override {
        ReaderAccountRepository repository;
        session->begin_transaction();
        repository.removeAccount(session, id);
        session->commit_transaction();
    }

private:
    int id;
};


#endif //SRC_DELETEREADERACCOUNTCOMMAND_H
