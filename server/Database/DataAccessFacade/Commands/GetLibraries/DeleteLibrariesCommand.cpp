//
// Created by Екатерина on 15.05.2022.
//

#include "DeleteLibrariesCommand.h"
void DeleteLibrariesCommand::execute(std::shared_ptr<Session> session)
{
    session->begin_transaction();
    repository->removeLibrary(session, id);
    session->commit_transaction();
}
