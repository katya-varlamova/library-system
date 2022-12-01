//
// Created by Екатерина on 11.05.2022.
//

#include "GetlibrariesCommand.h"
#include "../../../../Logger/Logger.h"

void GetlibrariesCommand::execute(std::shared_ptr<Session<>> session)
{
    session->begin_transaction();
    libs = repository->query(session, std::shared_ptr<LibarySpecification>(new GetLibrary(filters)));
    session->commit_transaction();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"libraries were found!");
}