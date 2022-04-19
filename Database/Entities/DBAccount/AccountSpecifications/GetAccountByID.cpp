//
// Created by Екатерина on 09.04.2022.
//

#include "GetAccountByID.h"
std::vector<DBAccount> GetAccountByID::exec(soci::session & session)
{
    std::vector<DBAccount> v_acc;
    DBAccount acc;
    soci::statement st = (session.prepare <<  "select * from public.Account where id = :id" , soci::into(acc), soci::use(id));
    st.execute();

    while (st.fetch())
        v_acc.push_back(acc);

    return v_acc;
}