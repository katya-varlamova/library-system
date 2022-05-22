//
// Created by Екатерина on 10.05.2022.
//

#include "ReturnBookCommand.h"
#include "../../../../Logger/Logger.h"

void ReturnBookCommand::execute(std::shared_ptr<Session> session)
{
    session->begin_transaction();
    repository->query(session, std::shared_ptr<ReturnBookSpecification>(new ReturnBookSpecification(login_lib, login_user, book_id)));
    session->commit_transaction();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"book was returned!");
}