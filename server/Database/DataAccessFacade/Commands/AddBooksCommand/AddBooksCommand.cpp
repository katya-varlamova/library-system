//
// Created by Екатерина on 10.04.2022.
//

#include "AddBooksCommand.h"
#include "../../../Entities/DBBook/BookRepository.h"
#include "../../../../Logger/Logger.h"

void AddBooksCommand::execute(std::shared_ptr<Session> session)
{
    for (int i = 0; i < books.size(); i++) {
        session->begin_transaction();
        repository->addBook(session, books[i]);
        session->commit_transaction();
    }
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"books added!");
}