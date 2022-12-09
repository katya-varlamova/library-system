//
// Created by Екатерина on 07.05.2022.
//

#ifndef SRC_SESSION_H
#define SRC_SESSION_H

#include <soci/session.h>
#include <libpq-fe.h>
#include <soci/soci.h>
#include <soci/postgresql/soci-postgresql.h>

#if TEST_CONFIGURATION==1
#include "../../test/TestingSession.h"
template<typename SESSION_T = TestingSession>
#endif
#if TEST_CONFIGURATION==0
template<typename SESSION_T = soci::session>
#endif
#if TEST_CONFIGURATION==2
template<typename SESSION_T = soci::session>
#endif
class Session {
public:
    Session(SESSION_T &session) : session(session) {}
    void begin_transaction();
    void commit_transaction();
    void rollback_transaction();
    void exec(const std::string &query);

    template<typename INTO_T>
    int exec_into(const std::string &query, INTO_T &into);

    template<typename INTO_T>
    int exec_into(const std::string &query, std::vector<INTO_T> &into);


private:
    SESSION_T &session;
};

#if TEST_CONFIGURATION==1
#include "TestSession.hpp"
#endif
#if TEST_CONFIGURATION==0
#include "SociSession.hpp"
#endif
#if TEST_CONFIGURATION==2
#include "BenchSession.hpp"
#endif
#endif//SRC_SESSION_H
