//
// Created by Екатерина on 07.05.2022.
//

#ifndef SRC_SESSION_H
#define SRC_SESSION_H

#include <soci/session.h>
#include <libpq-fe.h>
#include <soci/soci.h>

class Session {
public:
    Session(soci::session &session) : session(session) {}
    void begin_transaction();
    void commit_transaction();
    void rollback_transaction();
    void exec(const std::string &query);

    template<typename USE_T, typename INTO_T>
    int exec(const std::string &query, USE_T use, INTO_T &into);

    template<typename USE_T, typename INTO_T>
    int exec(const std::string &query, USE_T use, std::vector<INTO_T> &into);

    template<typename USE_T>
    void exec_using(const std::string &query, USE_T use);

    template<typename INTO_T>
    int exec_into(const std::string &query, INTO_T &into);

    template<typename INTO_T>
    int exec_into(const std::string &query, std::vector<INTO_T> &into);


private:
    soci::session &session;
};
template<typename USE_T>
void Session::exec_using(const std::string &query, USE_T use)
{
    session << query, soci::use(use);
}
template<typename INTO_T>
int Session::exec_into(const std::string &query, INTO_T &into)
{
    soci::indicator ind = soci::i_ok;
    session << query, soci::into(into, ind);
    if (ind == soci::i_ok)
        return 0;
    else
        return 1;
}
template<typename INTO_T>
int Session::exec_into(const std::string &query, std::vector<INTO_T> &into)
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

template<typename USE_T, typename INTO_T>
int Session::exec(const std::string &query, USE_T use, INTO_T &into)
{
    soci::indicator ind = soci::i_ok;
    session << query, soci::use(use), soci::into(into, ind);
    if (ind == soci::i_ok)
        return 0;
    else
        return 1;
}
template<typename USE_T, typename INTO_T>
int Session::exec(const std::string &query, USE_T use, std::vector<INTO_T> &into)
{
    soci::indicator ind = soci::i_ok;
    INTO_T i;
    soci::statement st(session);
    st = (session.prepare <<  query, soci::into(i, ind), soci::use(use));
    st.execute();

    while (st.fetch())
        into.push_back(i);
    if (ind == soci::i_ok)
        return 0;
    else
        return 1;
}

#endif //SRC_SESSION_H
