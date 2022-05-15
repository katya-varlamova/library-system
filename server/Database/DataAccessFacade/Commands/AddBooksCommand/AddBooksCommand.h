//
// Created by Екатерина on 10.04.2022.
//

#ifndef SRC_ADDBOOKSCOMMAND_H
#define SRC_ADDBOOKSCOMMAND_H

#include "../Command.h"
#include "../../../../Logic/Entities/Book/Book.h"
#include "../../../Entities/DBBook/BookRepository.h"
class AddBooksCommand : public Command{
public:
    AddBooksCommand(const std::vector<std::shared_ptr<Book>> &books)
    {
        this->books = books;
    }
    void execute(std::shared_ptr<Session> session) override;

protected:
    std::vector<std::shared_ptr<Book>> books;
};


#endif //SRC_ADDBOOKSCOMMAND_H
