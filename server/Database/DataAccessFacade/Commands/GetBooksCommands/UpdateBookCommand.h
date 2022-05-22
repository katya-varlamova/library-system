//
// Created by Екатерина on 11.05.2022.
//

#ifndef SRC_UPDATEBOOKCOMMAND_H
#define SRC_UPDATEBOOKCOMMAND_H


#include "../Command.h"
#include "../../../../Logic/Entities/Book/Book.h"
#include "../../../Entities/DBBook/BookSpecifications/GetFreeBooks.h"
#include "../../../Entities/DBBook/BookRepository.h"
#include "../../../Entities/DBBook/BookFilters/ByAuthorFilter.h"
class UpdateBookCommand : public Command{
public:
    UpdateBookCommand(std::shared_ptr<IBookRepository> repository, const std::shared_ptr<Book> &book)
    { this->repository = repository;
        this->book = book;}
    void execute(std::shared_ptr<Session> session) override;

private:
    std::shared_ptr<Book> book;
    std::shared_ptr<IBookRepository> repository;
};


#endif //SRC_UPDATEBOOKCOMMAND_H
