//
// Created by Екатерина on 04.04.2022.
//

#include "RegisterCommand.h"
void RegisterCommand::execute(soci::session &session)
{
    AccountRepository repository;
    repository.addAccount(session, acc);
}