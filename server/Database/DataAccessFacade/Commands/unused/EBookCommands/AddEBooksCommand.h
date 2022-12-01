//
// Created by Екатерина on 23.05.2022.
//

#ifndef SRC_ADDEBOOKS_H
#define SRC_ADDEBOOKS_H
#include "DataAccessFacade/Commands/Command.h"
#include "../../../../../Logic/Entities/EBook/EBook.h"
#include "Entities/DBEBook/IEBookRepository.h"
#include "../../../../../Logger/Logger.h"
class AddEBooksCommand : public Command{
public:
    AddEBooksCommand( const std::shared_ptr<IEBookRepository> &repository, const std::vector<std::shared_ptr<EBook>> &books)
    {
        this->books = books;
        this->repository = repository;
    }
    void execute(std::shared_ptr<Session<>> session) override
    {
        for (int i = 0; i < books.size(); i++) {
            session->begin_transaction();
            repository->addBook(session, books[i]);
            session->commit_transaction();
        }
        Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"ebooks added!");
    }

protected:
    std::shared_ptr<IEBookRepository> repository;
    std::vector<std::shared_ptr<EBook>> books;
};
#endif //SRC_ADDEBOOKS_H
