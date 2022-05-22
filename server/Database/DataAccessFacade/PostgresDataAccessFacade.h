//
// Created by Екатерина on 29.03.2022.
//

#ifndef SRC_POSTGRESDATAACCESSFACADE_H
#define SRC_POSTGRESDATAACCESSFACADE_H

#include "DataAccessFacade.h"
#include "../Connection/Connection.h"
#include "Commands/AuthCommand/AuthCommand.h"
#include "Commands/CreateDatabaseCommand/CreateDatabaseCommand.h"
#include "../../Logic/LogicException.h"
class PostgresDataAccessFacade : public DataAccessFacade{
public:
    PostgresDataAccessFacade() = default;
    void connectDB(const std::vector<std::string> &roles = std::vector<std::string>()) override;
    virtual void createDatabase() override;
    void execute(Command &command, std::string role = "admin") override;
    virtual void disconnectDB() override;

private:
    std::shared_ptr<Connection> conn;
};


#endif //SRC_POSTGRESDATAACCESSFACADE_H
