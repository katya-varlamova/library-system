//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_LIBRARIANACCOUNTCONVERTER_H
#define SRC_LIBRARIANACCOUNTCONVERTER_H
#include <memory>
#include "../../../../Logic/Entities/Account/LibrarianAccount.h"
#include "DBLibrarianAccount.h"

class LibrarianAccountConverter {
public:
    std::shared_ptr<LibrarianAccount> convert(std::shared_ptr<Account> account, int lib_id)
    {
        return std::shared_ptr<LibrarianAccount>(new LibrarianAccount(account, lib_id));
    }
    DBLibrarianAccount convert(int lib_id, int acc_id)
    {
        DBLibrarianAccount acc;
        acc.acc_id = acc_id;
        acc.lib_id = lib_id;
        return acc;
    }
};

#endif //SRC_LIBRARIANACCOUNTCONVERTER_H
