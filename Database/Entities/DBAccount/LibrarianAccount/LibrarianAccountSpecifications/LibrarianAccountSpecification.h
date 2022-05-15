//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_LIBRARIANACCOUNTSPECIFICATION_H
#define SRC_LIBRARIANACCOUNTSPECIFICATION_H
#include "../DBLibrarianAccount.h"
#include "../../../../Connection/Session.h"
class LibrarianAccountSpecification{
public:
    virtual std::vector<DBLibrarianAccount> exec(std::shared_ptr<Session> session) = 0;
};
#endif //SRC_LIBRARIANACCOUNTSPECIFICATION_H
