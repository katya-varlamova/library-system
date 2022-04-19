//
// Created by Екатерина on 10.04.2022.
//

#ifndef SRC_DATAACCESSMANAGER_H
#define SRC_DATAACCESSMANAGER_H

#include <memory>
#include "../Entities/Account/Account.h"
#include "../../Database/DataAccessFacade/DataAccessFacade.h"
#include "../../Database/DataAccessFacade/Commands/AuthCommand/AuthCommand.h"
#include "../../Database/DataAccessFacade/Commands/RegisterCommand/RegisterCommand.h"
#include "../LogicException.h"
#include "../../Database/DataAccessFacade/PostgresDataAccessFacade.h"

class DataAccessManager {
public:
    DataAccessManager()
    {
        facade = std::shared_ptr<DataAccessFacade>(new PostgresDataAccessFacade());
    }
    void create();
    void connect();
    void login(const std::string &login, const std::string &password);
    void registration(const std::shared_ptr<Account> &acc);
    void exec(const std::shared_ptr<Command> &com, const std::string &login, const std::string &password);
    void disconnect();
    void del();
protected:
    std::shared_ptr<DataAccessFacade> facade;
};


#endif //SRC_DATAACCESSMANAGER_H
