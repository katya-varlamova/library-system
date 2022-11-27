//
// Created by Екатерина on 10.05.2022.
//

#include "GetLibrarianAccount.h"
std::vector<DBLibrarianAccount> GetLibrarianAccount::exec(std::shared_ptr<Session<>> session) {
    std::vector<DBLibrarianAccount> v_acc;
    std::string fil_str;
    for (int i = 0; i < filters.size(); i++){
        if (i != filters.size() - 1)
            fil_str += filters[i]->getEqualClause() + " and ";
        else
            fil_str += filters[i]->getEqualClause();
    }
    std::string q_str;
    if (!filters.empty()) {
        q_str = "select LibrarianAccount.id, LibrarianAccount.acc_id, LibrarianAccount.lib_id "
                "from Account join LibrarianAccount on LibrarianAccount.acc_id = Account.id join Library on lib_id = Library.id "
                "where " + fil_str;
    } else
    {
        q_str = "select LibrarianAccount.id, LibrarianAccount.acc_id, LibrarianAccount.lib_id "
                "from Account join LibrarianAccount on LibrarianAccount.acc_id = Account.id join Library on lib_id = Library.id ";
    }
    session->exec_into(q_str, v_acc);
    return v_acc;
}