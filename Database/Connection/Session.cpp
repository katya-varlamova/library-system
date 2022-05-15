//
// Created by Екатерина on 07.05.2022.
//

#include "Session.h"
void Session::exec(const std::string &query)
{
    session << query;
}
void Session::begin_transaction()
{
    session.begin();
}
void Session::commit_transaction()
{
    session.commit();
}
void Session::rollback_transaction()
{
    session.rollback();
}