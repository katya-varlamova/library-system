//
// Created by Екатерина on 11.05.2022.
//

#include <Entities/DBLibrary/LibraryFilters/ByLibraryIDFilter.h>
#include <DatabseException.h>
#include "UpdateLibraries.h"
#include "../../../../Logger/Logger.h"

void UpdateLibrariesCommand::execute(std::shared_ptr<Session<>> session)
{
    session->begin_transaction();
    std::vector<std::shared_ptr<LibraryFilter>> lfs = {std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(lib->getID()))};
    auto res = repository->query(session, std::shared_ptr<LibarySpecification>(new GetLibrary(lfs)));
    if (res.empty()) {
        throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                "no such library!");
    }

    repository->updateLibrary(session, lib);

    session->commit_transaction();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"library was updated!");
}