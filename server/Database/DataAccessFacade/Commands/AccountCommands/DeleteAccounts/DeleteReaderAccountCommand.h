//
// Created by Екатерина on 15.05.2022.
//

#ifndef SRC_DELETEREADERACCOUNTCOMMAND_H
#define SRC_DELETEREADERACCOUNTCOMMAND_H

#include "DataAccessFacade/Commands/Command.h"
#include "Entities/DBAccount/ReaderAccount/IReaderAccountRepository.h"
class DeleteReaderAccountCommand: public Command {
public:
    DeleteReaderAccountCommand(std::shared_ptr<IReaderAccountRepository> repository,
                               std::shared_ptr<IAccountRepository> acc_repository,
                               int id) {
        this->id = id;
        this->repository = repository;
        this->acc_repository = acc_repository;
    }

    void execute(std::shared_ptr<Session<>> session) override {
        session->begin_transaction();
        std::vector<std::shared_ptr<AccountFilter>> fs = {std::shared_ptr<AccountFilter>(new ByAccountIDFilter(id))};
        auto res = acc_repository->query(session, std::shared_ptr<AccountSpecification>(new GetAccount(fs)));
        if (res.empty()) {
            throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                    "no such account!");
        }
        repository->removeAccount(session, id);
        session->commit_transaction();
        Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"reader account deleted!");
    }

private:
    int id;
    std::shared_ptr<IReaderAccountRepository> repository;
    std::shared_ptr<IAccountRepository> acc_repository;
};


#endif //SRC_DELETEREADERACCOUNTCOMMAND_H
