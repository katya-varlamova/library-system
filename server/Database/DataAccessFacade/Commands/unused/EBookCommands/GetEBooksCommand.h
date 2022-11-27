//
// Created by Екатерина on 23.05.2022.
//

#ifndef SRC_GETEBOOKS_H
#define SRC_GETEBOOKS_H
#include "DataAccessFacade/Commands/Command.h"
#include "../../../../../Logic/Entities/EBook/EBook.h"
#include "Entities/DBEBook/IEBookRepository.h"
#include "Entities/DBEBook/EBookRepository.h"
#include "Entities/DBBook/BookFilters/ByAuthorFilter.h"
#include "../../../../../Logger/Logger.h"
#include "Entities/DBEBook/EBookSpecifications/GetEBooksSpecification.h"
class GetEBooksCommand : public Command{
public:
    GetEBooksCommand(std::shared_ptr<IEBookRepository> repository, std::vector<std::shared_ptr<EBook>> &books, std::vector<std::shared_ptr<Filter>> &filters)
            : books(books) {
        this->filters = filters;
        this->repository = repository;
    }
    void execute(std::shared_ptr<Session<>> session) override
    {
        session->begin_transaction();
        books = repository->query(session, std::shared_ptr<EBookSpecification>(new GetEBooksSpecification(filters)));
        session->commit_transaction();
        Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"ebooks were found!");
    }

private:
    std::vector<std::shared_ptr<EBook>> &books;
    std::vector<std::shared_ptr<Filter>> filters;
    std::shared_ptr<IEBookRepository> repository;
};
#endif //SRC_GETEBOOKS_H
