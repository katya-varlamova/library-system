//
// Created by Екатерина on 10.05.2022.
//

#include "RegisterReaderCommand.h"
#include "../../../../../Logger/Logger.h"

void RegisterReaderCommand::execute(std::shared_ptr<Session<>> session)
{
    session->begin_transaction();
    repository->addAccount(session, acc);
    session->commit_transaction();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"reader was registered!");
}