//
// Created by Екатерина on 11.05.2022.
//

#ifndef SRC_UPDATELIBRARIANACCOUNTCOMMAND_H
#define SRC_UPDATELIBRARIANACCOUNTCOMMAND_H
#include "../Command.h"
#include "../../../Entities/DBAccount/LibrarianAccount/LibrarianAccountRepository.h"
class UpdateLibrarianAccountCommand: public Command{
public:
    UpdateLibrarianAccountCommand(const std::shared_ptr<LibrarianAccount> &acc){ this->acc = acc;}
    void execute(std::shared_ptr<Session> session) override
    {
        LibrarianAccountRepository repository;
        session->begin_transaction();
        repository.updateAccount(session, acc);
        session->commit_transaction();
    }

private:
    std::shared_ptr<LibrarianAccount> acc;
};
#endif //SRC_UPDATELIBRARIANACCOUNTCOMMAND_H
