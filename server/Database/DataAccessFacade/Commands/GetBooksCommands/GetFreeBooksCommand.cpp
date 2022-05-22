//
// Created by Екатерина on 08.05.2022.
//

#include "GetFreeBooksCommand.h"
void GetFreeBooksCommand::execute(std::shared_ptr<Session> session)
{
    session->begin_transaction();
    books = repository->query(session, std::shared_ptr<BookSpecification>(new GetFreeBooks(filters)));
    session->commit_transaction();
}