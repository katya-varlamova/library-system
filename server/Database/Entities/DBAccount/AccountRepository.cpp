//
// Created by Екатерина on 27.03.2022.
//

#include "AccountRepository.h"
#include "AccountFilters/ByAccountIDFilter.h"
#include "../DBBook/BookSpecifications/GetBooks.h"
#include "AccountSpecifications/GetAccount.h"

std::vector<std::shared_ptr<Account>> AccountRepository::query(std::shared_ptr<Session> session, std::shared_ptr<AccountSpecification> specification)
{
    std::vector<DBAccount> dbacc = specification->exec(session);
    std::vector<std::shared_ptr<Account>> vec;
    AccountConverter converter;
    for (auto &i : dbacc)
        vec.push_back(converter.convert(i));
    return vec;
}
int AccountRepository::addAccount(std::shared_ptr<Session> session, std::shared_ptr<Account> account)
{
    AccountConverter converter;
    DBAccount dbacc = converter.convert(account);
    int id;
    session->exec_using("insert into Account (login, password, name, role) values(:login, :password, :name, :role);", dbacc);
    session->exec_into("select max(id) "
                       "from Account;", id);
    return id;
}
void AccountRepository::updateAccount(std::shared_ptr<Session> session, std::shared_ptr<Account> account)
{
    std::vector<std::shared_ptr<AccountFilter>> fs = {std::shared_ptr<AccountFilter>(new ByAccountIDFilter(account->getID()))};
    auto res = query(session, std::shared_ptr<AccountSpecification>(new GetAccount(fs)));
    if (res.empty()) {
        throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                "no such account!");
    }
    std::string q = "update Account set login = '" + account->getLogin() + "', " +
                    "password = '" + account->getPassword() + "'," +
                    "name = '" + account->getName() + "' "
                    "where id = " + std::to_string(account->getID());
    session->exec(q);
}
void AccountRepository::removeAccount(std::shared_ptr<Session> session, int id)
{
    std::vector<std::shared_ptr<AccountFilter>> fs = {std::shared_ptr<AccountFilter>(new ByAccountIDFilter(id))};
    auto res = query(session, std::shared_ptr<AccountSpecification>(new GetAccount(fs)));
    if (res.empty()) {
        throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                "no such account!");
    }
    std::string q = "delete from Account "
                    "where id = " + std::to_string(id);
    session->exec(q);
}