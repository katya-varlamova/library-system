//
// Created by Екатерина on 28.03.2022.
//

#ifndef SRC_DATAACCESSFACADE_H
#define SRC_DATAACCESSFACADE_H


#include "Commands/Command.h"
#include "DataAccessFacade.h"
#include "../Connection/IConnectionPool.h"
#include "Commands/AccountCommands/AuthCommand/AuthCommand.h"

#include "../../Logic/LogicException.h"
class DataAccessFacade {
public:
    DataAccessFacade(const std::shared_ptr<IConnectionPool> &cp)
    {
        this->conn = cp;
    }
    void connectDB();
    void execute(Command &command, std::string role = "admin");
    void disconnectDB();

private:
    std::shared_ptr<IConnectionPool> conn;
};


#endif //SRC_DATAACCESSFACADE_H
