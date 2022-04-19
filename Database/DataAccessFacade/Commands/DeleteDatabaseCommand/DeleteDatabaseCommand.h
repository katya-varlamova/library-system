//
// Created by Екатерина on 18.04.2022.
//

#ifndef SRC_DELETEDATABASECOMMAND_H
#define SRC_DELETEDATABASECOMMAND_H

#include "../Command.h"
class DeleteDatabaseCommand : public Command{
public:
    DeleteDatabaseCommand()  = default;
    virtual void execute(soci::session & session) override;
};


#endif //SRC_DELETEDATABASECOMMAND_H
