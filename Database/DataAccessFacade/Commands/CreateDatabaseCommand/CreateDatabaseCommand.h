//
// Created by Екатерина on 04.04.2022.
//

#ifndef SRC_CREATEDATABASECOMMAND_H
#define SRC_CREATEDATABASECOMMAND_H

#include "../Command.h"
class CreateDatabaseCommand : public Command{
public:
    CreateDatabaseCommand()  = default;
    virtual void execute(soci::session & session) override;
};


#endif //SRC_CREATEDATABASECOMMAND_H
