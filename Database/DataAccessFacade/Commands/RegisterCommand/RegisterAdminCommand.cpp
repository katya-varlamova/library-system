//
// Created by Екатерина on 04.04.2022.
//

#include "RegisterAdminCommand.h"

void RegisterAdminCommand::execute(std::shared_ptr<Session> session)
{
    AdminAccountRepository repository;
    session->begin_transaction();
    repository.addAccount(session, acc);
    session->commit_transaction();
}