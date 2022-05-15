//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_RETURNBOOKCOMMAND_H
#define SRC_RETURNBOOKCOMMAND_H

#include "../Command.h"
#include "../../../../Logic/Entities/Book/Book.h"
#include "../../../Entities/DBBook/BookRepository.h"
#include "../../../Entities/DBBook/BookSpecifications/ReturnBookSpecification.h"
class ReturnBookCommand : public Command {
public:
    ReturnBookCommand(const std::string &login_user, const std::string &login_lib, std::shared_ptr<Book> book)
    {
        this->book = book;
        this->login_user = login_user;
        this->login_lib = login_lib;
    }
    void execute(std::shared_ptr<Session> session) override;
private:
    std::string login_user;
    std::string login_lib;
    std::shared_ptr<Book> book;
};


#endif //SRC_RETURNBOOKCOMMAND_H
