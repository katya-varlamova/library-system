//
// Created by Екатерина on 11.05.2022.
//

#include <Entities/DBBook/BookFilters/ByBookIDFilter.h>
#include <Entities/DBBook/BookSpecifications/GetBooks.h>
#include "UpdateBookCommand.h"
#include "../../../../Logger/Logger.h"

void UpdateBookCommand::execute(std::shared_ptr<Session<>> session) {
    session->begin_transaction();
    std::vector<std::shared_ptr<LibraryFilter>> lfs = {std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(book->getLibraryID()))};
    auto res = lib_repository->query(session, std::shared_ptr<LibarySpecification>(new GetLibrary(lfs)));
    if (res.empty()) {
        Logger::getInstance()->log(1, __FILE__, __LINE__, __TIME__,"no such library!");
        throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                "no such library!");
    }
    std::vector<std::shared_ptr<Filter>> fs = {std::shared_ptr<BookFilter>(new ByBookIDFilter(book->getID()))};
    auto b = repository->query(session, std::shared_ptr<BookSpecification>(new GetBooks(fs)));
    if (b.empty())
    {
        Logger::getInstance()->log(1, __FILE__, __LINE__, __TIME__,"no such library!");
        throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                "no such book!");
    }
    repository->updateBook(session, book);
    session->commit_transaction();
    Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"book was updated!");
}