//
// Created by Екатерина on 10.04.2022.
//

#include "DataAccessManager.h"
#include "../../Database/DataAccessFacade/Commands/DeleteDatabaseCommand/DeleteDatabaseCommand.h"

static struct
{
    std::string admin = "admin";
    std::string librarian = "librarian";
    std::string reader = "reader";
} roles;
void DataAccessManager::registration(const std::shared_ptr<Account> &account)
{
    int pos;
    std::vector<std::shared_ptr<Account>> acc;
    AuthCommand authCommand(account->getLogin(), acc);
    facade->execute(authCommand, roles.reader);
    if (!acc.empty()) {
        throw LogicException(__FILE__, __LINE__, __TIME__,
                             "user exists!");
    }
    RegisterCommand rc(account);
    facade->execute(rc, roles.admin);
}
void DataAccessManager::login(const std::string &login, const std::string &password)
{
    std::vector<std::shared_ptr<Account>> acc;
    AuthCommand authCommand(login, acc);
    facade->execute(authCommand, roles.reader);
    if (acc.empty())
        throw LogicException(__FILE__, __LINE__, __TIME__,
                             "no such user: registration is required");

    if (password != acc[0]->getPassword())
        throw LogicException(__FILE__, __LINE__, __TIME__,
                             "login failed");
}
void DataAccessManager::exec(const std::shared_ptr<Command> &command, const std::string &login, const std::string &password)
{
    int pos;
    std::vector<std::shared_ptr<Account>> acc;
    AuthCommand authCommand(login, acc);
    facade->execute(authCommand, roles.reader);
    if (acc.empty())
        throw LogicException(__FILE__, __LINE__, __TIME__,
                             "no such user: registration is required");

    if (password != acc[0]->getPassword())
        throw LogicException(__FILE__, __LINE__, __TIME__,
                                "login failed");
    facade->execute(*command, acc[0]->getRole());
}
void DataAccessManager::create()
{
    facade->createDatabase();
}
void DataAccessManager::connect()
{
    std::vector<std::string> r = {roles.librarian, roles.reader};
    facade->connectDB(r);
}
void DataAccessManager::disconnect()
{
    facade->disconnectDB();
}
void DataAccessManager::del()
{
    DeleteDatabaseCommand dd;
    facade->execute(dd, roles.admin);
}