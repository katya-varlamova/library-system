//
// Created by Екатерина on 10.05.2022.
//

#include "ReturnBookSpecification.h"
std::vector<DBBook> ReturnBookSpecification::exec(std::shared_ptr<Session> session)
{
    int id;
    int ok = session->exec_into("select return_book('" + login_user +
                                   "', '" + login_lib +
                                   "', '" + book->getName() +
                                   "', '" + book->getAuthor() + "')", id);
    if (ok != 0)
        throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                "impossible to return book!");
    return std::vector<DBBook>();
}