//
// Created by Екатерина on 11.05.2022.
//

#include "PostLibrariesCommand.h"
#include "../../../../Logger/Logger.h"

void PostLibrariesCommand::execute(std::shared_ptr<Session<>> session)
{
    session->begin_transaction();
    std::vector<std::shared_ptr<LibraryFilter>> filters = {
            std::shared_ptr<LibraryFilter>(new ByAddressFilter(lib->getAddress())),
            std::shared_ptr<LibraryFilter>(new ByLibraryNameFilter(lib->getName()))
    };
    std::vector<std::shared_ptr<Library>> libs = repository->query(session, std::shared_ptr<LibarySpecification>(new GetLibrary(filters)));

    if (libs.empty()) {
        repository->addLibrary(session, lib);
    }

    session->commit_transaction();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"library was added!");
}