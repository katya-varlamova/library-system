//
// Created by Екатерина on 15.05.2022.
//

#include <DatabseException.h>
#include <Entities/DBLibrary/LibraryFilters/ByLibraryIDFilter.h>
#include "DeleteLibrariesCommand.h"
#include "../../../../Logger/Logger.h"

void DeleteLibrariesCommand::execute(std::shared_ptr<Session<>> session)
{
    session->begin_transaction();
    std::vector<std::shared_ptr<LibraryFilter>> lfs = {std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(id))};
    auto res = repository->query(session, std::shared_ptr<LibarySpecification>(new GetLibrary(lfs)));
    if (res.empty()) {
        throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                "no such library!");
    }
    repository->removeLibrary(session, id);
    session->commit_transaction();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"library was deleted!");
}
