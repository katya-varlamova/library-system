//
// Created by Екатерина on 10.05.2022.
//

#include "RegisterLibrarianCommand.h"
#include "../../../../../Logger/Logger.h"

void RegisterLibrarianCommand::execute(std::shared_ptr<Session<>> session)
{
    session->begin_transaction();
    repository->addAccount(session, acc);
    session->commit_transaction();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"librarian was registered!");
}