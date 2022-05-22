//
// Created by Екатерина on 11.05.2022.
//

#include "UpdateBookCommand.h"
#include "../../../../Logger/Logger.h"

void UpdateBookCommand::execute(std::shared_ptr<Session> session) {
    session->begin_transaction();
    repository->updateBook(session, book);
    session->commit_transaction();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"book was updated!");
}