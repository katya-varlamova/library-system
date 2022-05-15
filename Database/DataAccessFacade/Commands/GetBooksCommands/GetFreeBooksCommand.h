//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_GETFREEBOOKSCOMMAND_H
#define SRC_GETFREEBOOKSCOMMAND_H

#include "../Command.h"
#include "../../../../Logic/Entities/Book/Book.h"
#include "../../../Entities/DBBook/BookSpecifications/GetFreeBooks.h"
#include "../../../Entities/DBBook/BookRepository.h"
#include "../../../Entities/DBBook/BookFilters/ByAuthorFilter.h"
class GetFreeBooksCommand : public Command{
public:
    GetFreeBooksCommand(std::vector<std::shared_ptr<Book>> &books, std::vector<std::shared_ptr<Filter>> &filters)
    : books(books) { this->filters = filters;}
    void execute(std::shared_ptr<Session> session) override;

private:
    std::vector<std::shared_ptr<Book>> &books;
    std::vector<std::shared_ptr<Filter>> filters;
};


#endif //SRC_GETFREEBOOKSCOMMAND_H
