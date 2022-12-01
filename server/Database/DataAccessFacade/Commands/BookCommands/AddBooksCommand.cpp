//
// Created by Екатерина on 10.04.2022.
//

#include "AddBooksCommand.h"
#include "Entities/DBBook/BookRepository.h"
#include "../../../../Logger/Logger.h"

void AddBooksCommand::execute(std::shared_ptr<Session<>> session)
{
    for (int i = 0; i < books.size(); i++) {
        session->begin_transaction();
        std::vector<std::shared_ptr<LibraryFilter>> lfs = {std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(books[i]->getLibraryID()))};
        auto res = lib_repository->query(session, std::shared_ptr<LibarySpecification>(new GetLibrary(lfs)));
        if (res.empty()) {
            Logger::getInstance()->log(1, __FILE__, __LINE__, __TIME__,"no such library!");
            throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                    "no such library!");
        }
        repository->addBook(session, books[i]);
        session->commit_transaction();
    }
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"books added!");
}