//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_GETLIBRARIANACCOUNTCOMMAND_H
#define SRC_GETLIBRARIANACCOUNTCOMMAND_H
#include "../Command.h"
#include "../../../Entities/DBAccount/LibrarianAccount/LibrarianAccountSpecifications/GetLibrarianAccount.h"
#include "../../../Entities/DBAccount/LibrarianAccount/LibrarianAccountSpecifications/LibrarianAccountSpecification.h"
#include "../../../Entities/DBAccount/LibrarianAccount/LibrarianAccountRepository.h"
class GetLibrarianAccountCommand: public Command{
public:
    GetLibrarianAccountCommand(std::shared_ptr<ILibrarianAccountRepository> repository, std::shared_ptr<LibrarianAccount> &acc, const std::vector<std::shared_ptr<AccountFilter>> &filters)
            : acc(acc) {
        this->filters = filters;
        this->repository = repository;
    }
    void execute(std::shared_ptr<Session> session) override
    {
        session->begin_transaction();
        std::vector<std::shared_ptr<LibrarianAccount>> accs = repository->query(session, std::shared_ptr<LibrarianAccountSpecification>(new GetLibrarianAccount(filters)));
        if (accs.size() == 1)
            acc = accs[0];
        session->commit_transaction();
    }

private:
    std::shared_ptr<LibrarianAccount> &acc;
    std::vector<std::shared_ptr<AccountFilter>> filters;
    std::shared_ptr<ILibrarianAccountRepository> repository;
};
#endif //SRC_GETLIBRARIANACCOUNTCOMMAND_H
