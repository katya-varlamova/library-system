//
// Created by Екатерина on 15.05.2022.
//

#include <Entities/DBBook/BookFilters/ByBookIDFilter.h>
#include <Entities/DBBook/BookSpecifications/GetBooks.h>
#include "DeleteBooksCommand.h"
#include "../../../../Logger/Logger.h"


void DeleteBooksCommand::execute(std::shared_ptr<Session<>> session)
{
    session->begin_transaction();
    std::vector<std::shared_ptr<Filter>> fs = {std::shared_ptr<BookFilter>(new ByBookIDFilter(id))};
    auto b = repository->query(session, std::shared_ptr<BookSpecification>(new GetBooks(fs)));
    if (b.empty())
    {
        Logger::getInstance()->log(1, __FILE__, __LINE__, __TIME__,"no such library!");
        throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                "no such book!");
    }
    repository->removeBook(session, id);
    session->commit_transaction();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"book was removed!");
}