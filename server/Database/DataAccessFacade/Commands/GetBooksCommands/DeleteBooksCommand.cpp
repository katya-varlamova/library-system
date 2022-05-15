//
// Created by Екатерина on 15.05.2022.
//

#include "DeleteBooksCommand.h"


void DeleteBooksCommand::execute(std::shared_ptr<Session> session)
{
    BookRepository repository;
    session->begin_transaction();
    repository.removeBook(session, id);
    session->commit_transaction();
}