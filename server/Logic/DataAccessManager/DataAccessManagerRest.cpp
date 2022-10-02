//
// Created by Екатерина on 29.09.2022.
//

#include "DataAccessManagerRest.h"
#include "../../Logger/Logger.h"

void DataAccessManagerRest::registration(const std::shared_ptr<AdminAccount> &account)
{
    int pos;
    std::vector<std::shared_ptr<Account>> acc;
    AuthCommand authCommand(ioc->getAccountRepository(), account->getAccount()->getLogin(), acc);
    facade->execute(authCommand, ioc->getReaderConnection()->getRoleString());
    if (!acc.empty()) {
        Logger::getInstance()->log(1, __FILE__, __LINE__, __TIME__,"user exists!");
        throw LogicException(__FILE__, __LINE__, __TIME__,
                             "user exists!");
    }
    RegisterAdminCommand rc(ioc->getAdminAccountRepository(), account);
    facade->execute(rc, ioc->getAdminConnection()->getRoleString());
}
void DataAccessManagerRest::registration(const std::shared_ptr<LibrarianAccount> &account)
{
    int pos;
    std::vector<std::shared_ptr<Account>> acc;
    AuthCommand authCommand(ioc->getAccountRepository(), account->getAccount()->getLogin(), acc);
    facade->execute(authCommand, ioc->getReaderConnection()->getRoleString());
    if (!acc.empty()) {
        Logger::getInstance()->log(1, __FILE__, __LINE__, __TIME__,"user exists!");
        throw LogicException(__FILE__, __LINE__, __TIME__,
                             "user exists!");
    }
    RegisterLibrarianCommand rc(ioc->getLibrarianAccountRepository(), account);
    facade->execute(rc, ioc->getAdminConnection()->getRoleString());
}
void DataAccessManagerRest::registration( const std::shared_ptr<ReaderAccount> &account)
{
    std::vector<std::shared_ptr<Account>> acc;
    AuthCommand authCommand(ioc->getAccountRepository(), account->getAccount()->getLogin(), acc);
    facade->execute(authCommand, ioc->getReaderConnection()->getRoleString());
    if (!acc.empty()) {
        Logger::getInstance()->log(1, __FILE__, __LINE__, __TIME__,"user exists!");
        throw LogicException(__FILE__, __LINE__, __TIME__,
                             "user exists!");
    }
    RegisterReaderCommand rc(ioc->getReaderAccountRepository(), account);
    facade->execute(rc, ioc->getAdminConnection()->getRoleString());
}
void DataAccessManagerRest::login(const std::string &login, const std::string &password, std::shared_ptr<Account> &account)
{
    std::vector<std::shared_ptr<Account>> acc;
    AuthCommand authCommand(ioc->getAccountRepository(), login, acc);
    facade->execute(authCommand, ioc->getReaderConnection()->getRoleString());
    if (acc.empty()) {
        Logger::getInstance()->log(1, __FILE__, __LINE__, __TIME__,"no such user: registration is required");
        throw LogicException(__FILE__, __LINE__, __TIME__,
                             "no such user: registration is required");
    }

    if (password != acc[0]->getPassword()) {
        Logger::getInstance()->log(1, __FILE__, __LINE__, __TIME__,"login failed");
        throw LogicException(__FILE__, __LINE__, __TIME__,
                             "login failed");
    }
    account = acc[0];
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"logged in successfully!");

}
void DataAccessManagerRest::exec( const std::shared_ptr<Command> &command, const std::string &role)// const std::string &login, const std::string &password)
{
    facade->execute(*command, role);
}
void DataAccessManagerRest::connect()
{
    facade->connectDB();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"connected to database!");
}
void DataAccessManagerRest::disconnect()
{
    facade->disconnectDB();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"disconnected from database!");
}