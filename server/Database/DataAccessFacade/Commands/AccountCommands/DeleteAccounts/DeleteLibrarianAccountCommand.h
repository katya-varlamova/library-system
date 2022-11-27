//
// Created by Екатерина on 15.05.2022.
//

#ifndef SRC_DELETELIBRARIANACCOUNTCOMMAND_H
#define SRC_DELETELIBRARIANACCOUNTCOMMAND_H


#include "DataAccessFacade/Commands/Command.h"
#include "Entities/DBAccount/LibrarianAccount/LibrarianAccountRepository.h"
#include "../../../../../Logger/Logger.h"

class DeleteLibrarianAccountCommand: public Command{
public:
    DeleteLibrarianAccountCommand(const std::shared_ptr<ILibrarianAccountRepository> &repository, std::shared_ptr<IAccountRepository> acc_repository,int id)
    {
        this->id = id;
        this->repository = repository;
        this->acc_repository = acc_repository;
    }
    void execute(std::shared_ptr<Session<>> session) override
    {
        session->begin_transaction();
        std::vector<std::shared_ptr<AccountFilter>> fs = {std::shared_ptr<AccountFilter>(new ByAccountIDFilter(id))};
        auto res = acc_repository->query(session, std::shared_ptr<AccountSpecification>(new GetAccount(fs)));
        if (res.empty()) {
            throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                    "no such account!");
        }
        repository->removeAccount(session, id);
        session->commit_transaction();
        Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"librarian account deleted!");
    }
private:
    int id;
    std::shared_ptr<ILibrarianAccountRepository> repository;
    std::shared_ptr<IAccountRepository> acc_repository;
};
#endif //SRC_DELETELIBRARIANACCOUNTCOMMAND_H
