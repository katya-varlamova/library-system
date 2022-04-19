//
// Created by Екатерина on 03.04.2022.
//

#include "GetAccountByLogin.h"

std::vector<DBAccount> GetAccountByLogin::exec(soci::session & session)
{
    std::vector<DBAccount> v_acc;
    DBAccount acc;
    soci::statement st = (session.prepare <<  "select * from public.Account where login = :login" , soci::into(acc), soci::use(login));
    st.execute();

    while (st.fetch())
        v_acc.push_back(acc);

    return v_acc;
}