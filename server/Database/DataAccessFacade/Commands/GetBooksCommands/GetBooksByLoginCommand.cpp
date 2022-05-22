//
// Created by Екатерина on 08.05.2022.
//

#include "GetBooksByLoginCommand.h"
#include "../../../../Logger/Logger.h"

void GetBooksByLoginCommand::execute(std::shared_ptr<Session> session)
{
    session->begin_transaction();
    books = repository->query(session, std::shared_ptr<BookSpecification>(new GetBooks(filters)));
    session->commit_transaction();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"books were found!");
}