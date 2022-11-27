//
// Created by Екатерина on 23.11.2022.
//

#ifndef SRC_LIBRARIANACCOUNTSPECIFICATIONSTUB_H
#define SRC_LIBRARIANACCOUNTSPECIFICATIONSTUB_H
#include "../Database/Entities/DBAccount/LibrarianAccount/LibrarianAccountSpecifications/LibrarianAccountSpecification.h"

class LibrarianAccountSpecificationStub : public LibrarianAccountSpecification {
public:
    LibrarianAccountSpecificationStub() = default;
    virtual std::vector<DBLibrarianAccount> exec(std::shared_ptr<Session<>> session) {
        session->exec("select LibrarianAccount.id, LibrarianAccount.acc_id, LibrarianAccount.lib_id from Account join LibrarianAccount on LibrarianAccount.acc_id = Account.id join Library on lib_id = Library.id where login = 'l1'");
        DBLibrarianAccount dbAccount;
        return std::vector<DBLibrarianAccount>({dbAccount});
    }
};
#endif //SRC_LIBRARIANACCOUNTSPECIFICATIONSTUB_H
