//
// Created by Екатерина on 11.05.2022.
//

#ifndef SRC_UPDATEREADERACCOUNTCOMMAND_H
#define SRC_UPDATEREADERACCOUNTCOMMAND_H
#include "../Command.h"
#include "../../../Entities/DBAccount/ReaderAccount/ReaderAccountRepository.h"
class UpdateReaderAccountCommand: public Command {
public:
    UpdateReaderAccountCommand(std::shared_ptr<IReaderAccountRepository> repository, const std::shared_ptr<ReaderAccount> &acc) {
        this->repository = repository;
        this->acc = acc; }

    void execute(std::shared_ptr<Session> session) override {
        session->begin_transaction();
        repository->updateAccount(session, acc);
        session->commit_transaction();
    }

private:
    std::shared_ptr<IReaderAccountRepository> repository;
    std::shared_ptr<ReaderAccount> acc;
};
#endif //SRC_UPDATEREADERACCOUNTCOMMAND_H
