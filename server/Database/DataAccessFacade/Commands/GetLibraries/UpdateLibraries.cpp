//
// Created by Екатерина on 11.05.2022.
//

#include "UpdateLibraries.h"
void UpdateLibrariesCommand::execute(std::shared_ptr<Session> session)
{
    LibraryRepository repository;
    session->begin_transaction();
    repository.updateLibrary(session, lib);
    session->commit_transaction();
}