//
// Created by Екатерина on 23.05.2022.
//

#ifndef SRC_UPDATEEBOOKS_H
#define SRC_UPDATEEBOOKS_H

#include "DataAccessFacade/Commands/Command.h"
#include "../../../../../Logic/Entities/EBook/EBook.h"
#include "Entities/DBEBook/EBookRepository.h"
#include "Entities/DBBook/BookFilters/ByAuthorFilter.h"
#include "../../../../../Logger/Logger.h"
class UpdateEBookCommand : public Command{
public:
    UpdateEBookCommand(std::shared_ptr<IEBookRepository> repository, const std::shared_ptr<EBook> &book)
    { this->repository = repository;
        this->book = book;}
    void execute(std::shared_ptr<Session<>> session) override
    {
        session->begin_transaction();
        repository->updateBook(session, book);
        session->commit_transaction();
        Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"ebook was updated!");
    }

private:
    std::shared_ptr<EBook> book;
    std::shared_ptr<IEBookRepository> repository;
};
#endif //SRC_UPDATEEBOOKS_H
