//
// Created by Екатерина on 11.05.2022.
//

#include "UpdateBookCommand.h"
void UpdateBookCommand::execute(std::shared_ptr<Session> session) {
    BookRepository repository;
    session->begin_transaction();
    repository.updateBook(session, book);
    session->commit_transaction();
}