//
// Created by Екатерина on 10.05.2022.
//

#include "TakeBookCommand.h"
#include "../../../../Logger/Logger.h"

void TakeBookCommand::execute(std::shared_ptr<Session> session)
{
    session->begin_transaction();
    repository->query(session, std::shared_ptr<TakeBookSpecification>(new TakeBookSpecification(login_lib, login_user, book_id)));
    session->commit_transaction();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"book was taken!");
}