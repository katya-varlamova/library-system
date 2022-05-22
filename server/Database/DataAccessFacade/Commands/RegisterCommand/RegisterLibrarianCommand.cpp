//
// Created by Екатерина on 10.05.2022.
//

#include "RegisterLibrarianCommand.h"
void RegisterLibrarianCommand::execute(std::shared_ptr<Session> session)
{
    session->begin_transaction();
    repository->addAccount(session, acc);
    session->commit_transaction();
}