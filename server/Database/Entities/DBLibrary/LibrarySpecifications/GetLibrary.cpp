//
// Created by Екатерина on 08.05.2022.
//

#include "GetLibrary.h"
std::vector<DBLibrary> GetLibrary::exec(std::shared_ptr<Session> session) {
    std::vector<DBLibrary> v_lib;
    std::string fil_str;
    for (int i = 0; i < filters.size(); i++){
        if (i != filters.size() - 1)
            fil_str += filters[i]->getEqualClause() + " and ";
        else
            fil_str += filters[i]->getEqualClause();
    }
    std::string q_str;
    if (!filters.empty()) {
        q_str = "select * "
                            "from Library "
                            "where " + fil_str;
    } else {
        q_str = "select * "
                "from Library ";
    }

    session->exec_into(q_str, v_lib);
    return v_lib;
}