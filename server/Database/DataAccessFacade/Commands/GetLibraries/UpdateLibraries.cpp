//
// Created by Екатерина on 11.05.2022.
//

#include "UpdateLibraries.h"
#include "../../../../Logger/Logger.h"

void UpdateLibrariesCommand::execute(std::shared_ptr<Session> session)
{
    session->begin_transaction();
    repository->updateLibrary(session, lib);
    session->commit_transaction();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"library was updated!");
}