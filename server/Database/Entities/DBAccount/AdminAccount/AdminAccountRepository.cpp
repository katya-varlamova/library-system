//
// Created by Екатерина on 10.05.2022.
//

#include "AdminAccountRepository.h"

std::vector<std::shared_ptr<AdminAccount>> AdminAccountRepository::query(const std::shared_ptr<Session> &session, std::shared_ptr<AdminAccountSpecification> specification)
{
    std::vector<DBAdminAccount> dbacc = specification->exec(session);
    std::vector<std::shared_ptr<AdminAccount>> vec;
    AdminAccountConverter converter;
    AccountRepository ar;
    for (auto &i : dbacc) {
        std::vector<std::shared_ptr<Account>> accs = ar.query(session, std::shared_ptr<AccountSpecification>(new GetAccount({std::shared_ptr<AccountFilter>(new ByAccountIDFilter(i.acc_id))})));
        if (accs.size() == 1)
            vec.push_back(converter.convert(accs[0]));
    }
    return vec;
}
void AdminAccountRepository::addAccount(const std::shared_ptr<Session> &session, std::shared_ptr<AdminAccount> account)
{

    AccountRepository ar;
    int acc_id = ar.addAccount(session, account->getAccount());
    AdminAccountConverter aac;
    DBAdminAccount dbacc = aac.convert(acc_id);
    session->exec_using("insert into AdminAccount (acc_id) "
                        "values(:acc_id)", dbacc);
}
void AdminAccountRepository::updateAccount(const std::shared_ptr<Session> &session, std::shared_ptr<AdminAccount> account)
{
    AccountRepository ar;
    ar.updateAccount(session, account->getAccount());
}
void AdminAccountRepository::removeAccount(const std::shared_ptr<Session> &session, int id)
{
    std::string q = "delete from AdminAccount "
                    "where acc_id = " + std::to_string(id);
    session->exec(q);
    AccountRepository repository;
    repository.removeAccount(session, id);
}