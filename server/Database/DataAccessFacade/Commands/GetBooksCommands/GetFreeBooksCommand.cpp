//
// Created by Екатерина on 08.05.2022.
//

#include "GetFreeBooksCommand.h"
#include "../../../../Logger/Logger.h"

void GetFreeBooksCommand::execute(std::shared_ptr<Session> session)
{
    session->begin_transaction();
    books = repository->query(session, std::shared_ptr<BookSpecification>(new GetFreeBooks(filters)));
    session->commit_transaction();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"free books were found!");
}