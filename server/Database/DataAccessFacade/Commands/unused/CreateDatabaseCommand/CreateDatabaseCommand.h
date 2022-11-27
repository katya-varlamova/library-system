//
// Created by Екатерина on 04.04.2022.
//

#ifndef SRC_CREATEDATABASECOMMAND_H
#define SRC_CREATEDATABASECOMMAND_H

#include "DataAccessFacade/Commands/Command.h"
class CreateDatabaseCommand : public Command{
public:
    CreateDatabaseCommand()  = default;
    virtual void execute(std::shared_ptr<Session<>> session) override;
};


#endif //SRC_CREATEDATABASECOMMAND_H
