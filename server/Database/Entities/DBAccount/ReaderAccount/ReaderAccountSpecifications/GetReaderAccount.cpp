//
// Created by Екатерина on 10.05.2022.
//

#include "GetReaderAccount.h"
std::vector<DBReaderAccount> GetReaderAccount::exec(std::shared_ptr<Session> session)
{
    std::vector<DBReaderAccount> v_acc;
    std::string fil_str;
    for (int i = 0; i < filters.size(); i++) {
        if (i != filters.size() - 1)
            fil_str += filters[i]->getEqualClause() + " and ";
        else
            fil_str += filters[i]->getEqualClause();
    }
    std::string q_str;
    if (!filters.empty()) {
        q_str = "select ReaderAccount.id, ReaderAccount.acc_id, phone "
                 "from Account join ReaderAccount on ReaderAccount.acc_id = Account.id "
                 "where " + fil_str;
    }
    else
    {
        q_str = "select ReaderAccount.id, ReaderAccount.acc_id, phone "
                "from Account join ReaderAccount on ReaderAccount.acc_id = Account.id ";
    }

    session->exec_into(q_str, v_acc);
    return v_acc;
}