//
// Created by Екатерина on 08.05.2022.
//

#include "GetAccount.h"
std::vector<DBAccount> GetAccount::exec(std::shared_ptr<Session<>> session)
{
    std::vector<DBAccount> v_acc;
    std::string fil_str;
    for (int i = 0; i < filters.size(); i++) {
        if (i != filters.size() - 1)
            fil_str += filters[i]->getEqualClause() + " and ";
        else
            fil_str += filters[i]->getEqualClause();
    }
    std::string q_str;
    if (!filters.empty()) {
        q_str = "select * from Account "
                "where " + fil_str;
    } else
    {
        q_str = "select * from Account ";
    }
    session->exec_into(q_str, v_acc);
    return v_acc;
}