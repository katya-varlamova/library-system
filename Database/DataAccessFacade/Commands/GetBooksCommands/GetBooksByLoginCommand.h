//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_GETBOOKSBYLOGINCOMMAND_H
#define SRC_GETBOOKSBYLOGINCOMMAND_H


#include "../Command.h"
#include "../../../../Logic/Entities/Book/Book.h"
#include "../../../Entities/DBBook/BookSpecifications/GetBooks.h"
#include "../../../Entities/DBBook/BookRepository.h"
#include "../../../Entities/DBBook/BookFilters/ByAuthorFilter.h"
class GetBooksByLoginCommand : public Command{
public:
    GetBooksByLoginCommand(std::vector<std::shared_ptr<Book>> &books, std::vector<std::shared_ptr<Filter>> &filters)
            : books(books) { this->filters = filters;}
    void execute(std::shared_ptr<Session> session) override;

private:
    std::vector<std::shared_ptr<Book>> &books;
    std::vector<std::shared_ptr<Filter>> filters;
};

#endif //SRC_GETBOOKSBYLOGINCOMMAND_H
