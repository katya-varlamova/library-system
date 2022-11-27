//
// Created by Екатерина on 19.11.2022.
//

#ifndef SRC_SOCISESSION_HPP
#define SRC_SOCISESSION_HPP
#include "Session.h"

template<>
template<typename INTO_T>
int Session<soci::session>::exec_into(const std::string &query, INTO_T &into)
{
    soci::indicator ind = soci::i_ok;
    session << query, soci::into(into, ind);
    if (ind == soci::i_ok)
        return 0;
    else
        return 1;
}
template<>
template<typename INTO_T>
int Session<soci::session>::exec_into(const std::string &query, std::vector<INTO_T> &into)
{
    soci::indicator ind = soci::i_ok;
    INTO_T i;
    soci::statement st(session);
    st = (session.prepare <<  query, soci::into(i, ind));

    st.execute();

    while (st.fetch())
        into.push_back(i);
    if (ind == soci::i_ok)
        return 0;
    else
        return 1;
}

#endif //SRC_SOCISESSION_HPP
