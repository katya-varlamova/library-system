//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_GETREADERACCOUNTCOMMAND_H
#define SRC_GETREADERACCOUNTCOMMAND_H
#include "../Command.h"
#include "../../../Entities/DBAccount/ReaderAccount/ReaderAccountSpecifications/GetReaderAccount.h"
#include "../../../Entities/DBAccount/ReaderAccount/ReaderAccountSpecifications/ReaderAccountSpecification.h"
#include "../../../Entities/DBAccount/ReaderAccount/IReaderAccountRepository.h"
class GetReaderAccountCommand: public Command{
public:
    GetReaderAccountCommand(std::shared_ptr<IReaderAccountRepository> repository, std::shared_ptr<ReaderAccount> &acc, const std::vector<std::shared_ptr<AccountFilter>> &filters)
    : acc(acc) {
        this->filters = filters;
        this->repository = repository;
    }
    void execute(std::shared_ptr<Session> session) override
    {
        session->begin_transaction();
        std::vector<std::shared_ptr<ReaderAccount>> accs = repository->query(session, std::shared_ptr<ReaderAccountSpecification>(new GetReaderAccount(filters)));
        if (accs.size() == 1)
            acc = accs[0];
        session->commit_transaction();
    }

private:
    std::shared_ptr<ReaderAccount> &acc;
    std::vector<std::shared_ptr<AccountFilter>> filters;
    std::shared_ptr<IReaderAccountRepository> repository;
};
#endif //SRC_GETREADERACCOUNTCOMMAND_H
