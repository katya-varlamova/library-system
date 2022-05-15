//
// Created by Екатерина on 10.05.2022.
//

#include "RegisterReaderCommand.h"
void RegisterReaderCommand::execute(std::shared_ptr<Session> session)
{
    ReaderAccountRepository repository;
    session->begin_transaction();
    repository.addAccount(session, acc);
    session->commit_transaction();
}