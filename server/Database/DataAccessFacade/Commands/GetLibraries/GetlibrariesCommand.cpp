//
// Created by Екатерина on 11.05.2022.
//

#include "GetlibrariesCommand.h"
void GetlibrariesCommand::execute(std::shared_ptr<Session> session)
{
    session->begin_transaction();
    libs = repository->query(session, std::shared_ptr<LibarySpecification>(new GetLibrary(filters)));
    session->commit_transaction();
}