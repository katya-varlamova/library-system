//
// Created by Екатерина on 07.05.2022.
//

#include "Session.h"
#if TEST_CONFIGURATION==0
template<>
void Session<>::exec(const std::string &query)
{
    session << query;
}
template<>
void Session<>::begin_transaction()
{
    session.begin();
}
template<>
void Session<>::commit_transaction()
{
    session.commit();
}
template<>
void Session<>::rollback_transaction()
{
    session.rollback();
}
#endif
#if TEST_CONFIGURATION==1
template<>
void Session<TestingSession>::exec(const std::string &query)
{
    session.analyze(query);
}
template<>
void Session<TestingSession>::begin_transaction()
{
}
template<>
void Session<TestingSession>::commit_transaction()
{
}
template<>
void Session<TestingSession>::rollback_transaction()
{
}
template <>
template <>
int Session<TestingSession>::exec_into(const std::string &query, int &into)
{
    session.analyze(query);
    into = 1;
    return 0;
}
#endif
#if TEST_CONFIGURATION==2
#include <sys/time.h>
template<>
void Session<>::exec(const std::string &query)
{
//    clock_t sTime = clock();
    session << query;
//    clock_t eTime = clock();
//    double time = (eTime - sTime) / (.001 * CLOCKS_PER_SEC);
//    printf("%lf\n", time);
}
template<>
void Session<>::begin_transaction()
{
    session.begin();
}
template<>
void Session<>::commit_transaction()
{
    session.commit();
}
template<>
void Session<>::rollback_transaction()
{
    session.rollback();
}
#endif