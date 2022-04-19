//
// Created by Екатерина on 18.04.2022.
//

#include "DeleteDatabaseCommand.h"
void DeleteDatabaseCommand::execute(soci::session &session)
{
    session << "drop table bookitem; "
               "drop table book; "
               "drop table library; "
               "drop table account;";

}