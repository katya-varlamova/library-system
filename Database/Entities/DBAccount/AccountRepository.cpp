//
// Created by Екатерина on 27.03.2022.
//

#include "AccountRepository.h"
std::vector<std::shared_ptr<Account>> AccountRepository::query(soci::session & session, std::shared_ptr<AccountSpecification> specification)
{
    std::vector<DBAccount> dbacc = specification->exec(session);
    std::vector<std::shared_ptr<Account>> vec;
    AccountConverter converter;
    for (auto &i : dbacc)
        vec.push_back(converter.convert(i));
    return vec;
}
void AccountRepository::addAccount(soci::session & session, std::shared_ptr<Account> account)
{
    AccountConverter converter;
    DBAccount dbacc = converter.convert(account);
    session <<  "insert into public.Account values(default, :login, :password, :name, :role)", soci::use(dbacc);
}