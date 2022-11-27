//
// Created by Екатерина on 29.09.2022.
//

#ifndef SRC_DATAACCESSMANAGERREST_H
#define SRC_DATAACCESSMANAGERREST_H


#include <memory>
#include "../Entities/Account/Account.h"
#include "../../Database/DataAccessFacade/DataAccessFacade.h"
#include "../../Database/DataAccessFacade/Commands/AccountCommands/AuthCommand/AuthCommand.h"
#include "../../Database/DataAccessFacade/Commands/AccountCommands/RegisterCommand/RegisterAdminCommand.h"
#include "../LogicException.h"
#include "../../Database/DataAccessFacade/Commands/Filters/Filter.h"
#include "../Entities/Account/ReaderAccount.h"
#include "../Entities/Account/LibrarianAccount.h"
//#include "../../Database/DataAccessFacade/Commands/DeleteDatabaseCommand/DeleteDatabaseCommand.h"
#include "../../Database/DataAccessFacade/Commands/AccountCommands/RegisterCommand/RegisterLibrarianCommand.h"
#include "../../Database/DataAccessFacade/Commands/AccountCommands/RegisterCommand/RegisterReaderCommand.h"
#include "../../Database/SqlIoc/IocRepository.h"

class DataAccessManagerRest {
public:
    explicit DataAccessManagerRest(const std::shared_ptr<IIocRepository> &ioc)
    {
        this->ioc = ioc;
        facade = std::shared_ptr<DataAccessFacade>(new DataAccessFacade(ioc->getConnectionPool()));
    }
    void connect();
    void login(const std::string &login, const std::string &password, std::shared_ptr<Account> &account);
    void registration(const std::shared_ptr<ReaderAccount> &acc);
    void registration( const std::shared_ptr<AdminAccount> &acc);
    void registration( const std::shared_ptr<LibrarianAccount> &acc);
    void exec(const std::shared_ptr<Command> &com, const std::string &role);
    void disconnect();
protected:
    std::shared_ptr<DataAccessFacade> facade;
    std::shared_ptr<IIocRepository> ioc;
};
#endif //SRC_DATAACCESSMANAGERREST_H
