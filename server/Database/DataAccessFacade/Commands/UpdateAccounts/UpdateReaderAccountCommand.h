//
// Created by Екатерина on 11.05.2022.
//

#ifndef SRC_UPDATEREADERACCOUNTCOMMAND_H
#define SRC_UPDATEREADERACCOUNTCOMMAND_H
#include "../Command.h"
#include "../../../Entities/DBAccount/ReaderAccount/ReaderAccountRepository.h"
class UpdateReaderAccountCommand: public Command {
public:
    UpdateReaderAccountCommand(const std::shared_ptr<ReaderAccount> &acc) { this->acc = acc; }

    void execute(std::shared_ptr<Session> session) override {
        ReaderAccountRepository repository;
        session->begin_transaction();
        repository.updateAccount(session, acc);
        session->commit_transaction();
    }

private:
    std::shared_ptr<ReaderAccount> acc;
};
#endif //SRC_UPDATEREADERACCOUNTCOMMAND_H
