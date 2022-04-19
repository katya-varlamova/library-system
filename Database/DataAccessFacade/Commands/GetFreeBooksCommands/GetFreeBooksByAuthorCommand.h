//
// Created by Екатерина on 10.04.2022.
//

#ifndef SRC_GETFREEBOOKSBYAUTHORCOMMAND_H
#define SRC_GETFREEBOOKSBYAUTHORCOMMAND_H


#include "../Command.h"
#include "../../../../Logic/Entities/Book/Book.h"
#include "../../../Entities/DBBook/BookSpecifications/GetFreeBooksByAuthorSpec.h"
#include "../../../Entities/DBBook/BookRepository.h"
class GetFreeBooksByAuthorCommand : public Command{
public:
    GetFreeBooksByAuthorCommand(std::vector<std::shared_ptr<Book>> &books, std::string author)
            : books(books) { this->author = author;}
    void execute(soci::session &session) override;

private:
    std::vector<std::shared_ptr<Book>> &books;
    std::string author;
};


#endif //SRC_GETFREEBOOKSBYAUTHORCOMMAND_H
