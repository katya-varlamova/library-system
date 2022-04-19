//
// Created by Екатерина on 29.03.2022.
//

#ifndef SRC_COMMAND_H
#define SRC_COMMAND_H


#include <soci/session.h>

class Command {
public:
    virtual void execute(soci::session & session) = 0 ;
};


#endif //SRC_COMMAND_H
