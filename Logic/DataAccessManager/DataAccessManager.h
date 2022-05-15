//
// Created by Екатерина on 10.04.2022.
//

#ifndef SRC_DATAACCESSMANAGER_H
#define SRC_DATAACCESSMANAGER_H

#include <memory>
#include "../Entities/Account/Account.h"
#include "../../Database/DataAccessFacade/DataAccessFacade.h"
#include "../../Database/DataAccessFacade/Commands/AuthCommand/AuthCommand.h"
#include "../../Database/DataAccessFacade/Commands/RegisterCommand/RegisterAdminCommand.h"
#include "../LogicException.h"
#include "../../Database/DataAccessFacade/PostgresDataAccessFacade.h"
#include "../../Database/DataAccessFacade/Commands/Filters/Filter.h"
#include "../Entities/Account/ReaderAccount.h"
#include "../Entities/Account/LibrarianAccount.h"
#include "../../Database/DataAccessFacade/Commands/DeleteDatabaseCommand/DeleteDatabaseCommand.h"
#include "../../Database/DataAccessFacade/Commands/RegisterCommand/RegisterLibrarianCommand.h"
#include "../../Database/DataAccessFacade/Commands/RegisterCommand/RegisterReaderCommand.h"

class DataAccessManager {
public:
    DataAccessManager()
    {
        facade = std::shared_ptr<DataAccessFacade>(new PostgresDataAccessFacade());
    }
    void create();
    void connect();
    void login(const std::string &login, const std::string &password, std::shared_ptr<Account> &account);
    void registration(const std::shared_ptr<ReaderAccount> &acc);
    void registration(const std::shared_ptr<AdminAccount> &acc);
    void registration(const std::shared_ptr<LibrarianAccount> &acc);
    void exec(const std::shared_ptr<Command> &com, const std::string &login, const std::string &password);
    void disconnect();
    void del();
protected:
    std::shared_ptr<DataAccessFacade> facade;
};


#endif //SRC_DATAACCESSMANAGER_H
