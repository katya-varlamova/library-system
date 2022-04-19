//
// Created by Екатерина on 04.04.2022.
//

#ifndef SRC_GETFREEBOOKSBYNAMECOMMAND_H
#define SRC_GETFREEBOOKSBYNAMECOMMAND_H

#include "../Command.h"
#include "../../../../Logic/Entities/Book/Book.h"
#include "../../../Entities/DBBook/BookSpecifications/GetFreeBooksByNameSpec.h"
#include "../../../Entities/DBBook/BookRepository.h"
class GetFreeBooksByNameCommand : public Command{
public:
    GetFreeBooksByNameCommand(std::vector<std::shared_ptr<Book>> &books, std::string name)
    : books(books) { this->name = name;}
    void execute(soci::session &session) override;

private:
    std::vector<std::shared_ptr<Book>> &books;
    std::string name;
};


#endif //SRC_GETFREEBOOKSBYNAMECOMMAND_H
