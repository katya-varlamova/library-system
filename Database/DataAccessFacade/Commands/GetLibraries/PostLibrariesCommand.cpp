//
// Created by Екатерина on 11.05.2022.
//

#include "PostLibrariesCommand.h"
void PostLibrariesCommand::execute(std::shared_ptr<Session> session)
{
    LibraryRepository repository;
    session->begin_transaction();
    repository.addLibrary(session, lib);
    session->commit_transaction();
}