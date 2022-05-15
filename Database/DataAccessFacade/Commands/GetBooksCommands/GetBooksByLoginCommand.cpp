//
// Created by Екатерина on 08.05.2022.
//

#include "GetBooksByLoginCommand.h"

void GetBooksByLoginCommand::execute(std::shared_ptr<Session> session)
{
    BookRepository repository;
    session->begin_transaction();
    books = repository.query(session, std::shared_ptr<BookSpecification>(new GetBooks(filters)));
    session->commit_transaction();
}