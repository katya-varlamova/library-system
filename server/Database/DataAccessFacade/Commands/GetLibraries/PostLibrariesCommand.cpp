//
// Created by Екатерина on 11.05.2022.
//

#include "PostLibrariesCommand.h"
#include "../../../../Logger/Logger.h"

void PostLibrariesCommand::execute(std::shared_ptr<Session> session)
{
    session->begin_transaction();
    repository->addLibrary(session, lib);
    session->commit_transaction();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"library was added!");
}