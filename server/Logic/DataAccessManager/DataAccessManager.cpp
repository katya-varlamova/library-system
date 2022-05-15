//
// Created by Екатерина on 10.04.2022.
//

#include "DataAccessManager.h"
static struct
{
    std::string admin = "admin";
    std::string librarian = "librarian";
    std::string reader = "reader";
} roles;
void DataAccessManager::registration(const std::shared_ptr<AdminAccount> &account)
{
    int pos;
    std::vector<std::shared_ptr<Account>> acc;
    AuthCommand authCommand(account->getAccount()->getLogin(), acc);
    facade->execute(authCommand, roles.reader);
    if (!acc.empty()) {
        throw LogicException(__FILE__, __LINE__, __TIME__,
                             "user exists!");
    }
    RegisterAdminCommand rc(account);
    facade->execute(rc, roles.admin);
}
void DataAccessManager::registration(const std::shared_ptr<LibrarianAccount> &account)
{
    int pos;
    std::vector<std::shared_ptr<Account>> acc;
    AuthCommand authCommand(account->getAccount()->getLogin(), acc);
    facade->execute(authCommand, roles.reader);
    if (!acc.empty()) {
        throw LogicException(__FILE__, __LINE__, __TIME__,
                             "user exists!");
    }
    RegisterLibrarianCommand rc(account);
    facade->execute(rc, roles.admin);
}
void DataAccessManager::registration(const std::shared_ptr<ReaderAccount> &account)
{
    int pos;
    std::vector<std::shared_ptr<Account>> acc;
    AuthCommand authCommand(account->getAccount()->getLogin(), acc);
    facade->execute(authCommand, roles.reader);
    if (!acc.empty()) {
        throw LogicException(__FILE__, __LINE__, __TIME__,
                             "user exists!");
    }
    RegisterReaderCommand rc(account);
    facade->execute(rc, roles.admin);
}
void DataAccessManager::login(const std::string &login, const std::string &password, std::shared_ptr<Account> &account)
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
    account = acc[0];

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