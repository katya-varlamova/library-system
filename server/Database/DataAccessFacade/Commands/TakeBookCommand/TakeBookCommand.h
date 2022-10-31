//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_TAKEBOOKCOMMAND_H
#define SRC_TAKEBOOKCOMMAND_H

#include "../Command.h"
#include "../../../../Logic/Entities/Book/Book.h"
#include "../../../Entities/DBBook/BookRepository.h"
#include "../../../Entities/DBBook/BookSpecifications/TakeBookSpecification.h"
#include "../../../Entities/DBAccount/AdminAccount/IAdminAccountRepository.h"

class TakeBookCommand : public Command{
public:
    TakeBookCommand(std::shared_ptr<IAccountRepository> r, std::shared_ptr<IBookRepository> repository, const std::string &login_user, const std::string &login_lib, int book_id)
    {
        this->book_id = book_id;
        this->login_user = login_user;
        this->login_lib = login_lib;
        this->repository = repository;
        this->r = r;
    }
    void execute(std::shared_ptr<Session> session) override;

private:
    std::string login_user;
    std::string login_lib;
    int book_id;
    std::shared_ptr<IBookRepository> repository;
    std::shared_ptr<IAccountRepository> r;
};


#endif //SRC_TAKEBOOKCOMMAND_H
