//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_RETURNBOOKSPECIFICATION_H
#define SRC_RETURNBOOKSPECIFICATION_H

#include "BookSpecification.h"
#include "../../../../Logic/Entities/Account/LibrarianAccount.h"
#include "../../../../Logic/Entities/Account/ReaderAccount.h"
#include "../../../../Logic/Entities/Book/Book.h"
class ReturnBookSpecification : public BookSpecification{
public:
    ReturnBookSpecification(const std::string &login_lib, const std::string &login_user, int book_id)
    {
        this->book_id = book_id;
        this->login_user = login_user;
        this->login_lib = login_lib;
    }
    std::vector<DBBook> exec(std::shared_ptr<Session<>> session) override;
private:
    std::string login_user;
    std::string login_lib;
    int book_id;
};


#endif //SRC_RETURNBOOKSPECIFICATION_H
