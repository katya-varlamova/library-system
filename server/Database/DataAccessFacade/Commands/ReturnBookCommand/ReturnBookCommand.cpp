//
// Created by Екатерина on 10.05.2022.
//

#include "ReturnBookCommand.h"
void ReturnBookCommand::execute(std::shared_ptr<Session> session)
{
    BookRepository repository;
    session->begin_transaction();
    repository.query(session, std::shared_ptr<ReturnBookSpecification>(new ReturnBookSpecification(login_lib, login_user, book)));
    session->commit_transaction();
}