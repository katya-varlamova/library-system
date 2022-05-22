//
// Created by Екатерина on 28.03.2022.
//

#ifndef SRC_DATAACCESSFACADE_H
#define SRC_DATAACCESSFACADE_H


#include "Commands/Command.h"
#include "../../Logic/Entities/Account/Account.h"

class DataAccessFacade {
public:
    virtual void connectDB(const std::vector<std::string> &roles = std::vector<std::string>()) = 0;
    virtual void createDatabase() = 0;
    virtual void execute(Command &command, std::string role = "admin") = 0;
    virtual void disconnectDB() = 0;
};


#endif //SRC_DATAACCESSFACADE_H
