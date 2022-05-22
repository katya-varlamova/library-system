//
// Created by Екатерина on 15.05.2022.
//

#include "DeleteBooksCommand.h"
#include "../../../../Logger/Logger.h"


void DeleteBooksCommand::execute(std::shared_ptr<Session> session)
{
    session->begin_transaction();
    repository->removeBook(session, id);
    session->commit_transaction();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"book was removed!");
}