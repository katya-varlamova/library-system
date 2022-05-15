//
// Created by Екатерина on 29.03.2022.
//

#ifndef SRC_COMMAND_H
#define SRC_COMMAND_H

#include "../../Connection/Session.h"

class Command {
public:
    virtual void execute(std::shared_ptr<Session> session) = 0 ;
};


#endif //SRC_COMMAND_H
