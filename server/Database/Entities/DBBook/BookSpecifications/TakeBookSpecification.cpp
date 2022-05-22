//
// Created by Екатерина on 17.04.2022.
//

#include "TakeBookSpecification.h"
#include "../../../../Logger/Logger.h"

std::vector<DBBook> TakeBookSpecification::exec(std::shared_ptr<Session> session)
{
    int id;
    std::string q = "select take_book('" + login_user +
                   "', '" + login_lib +
                   "', '" + std::to_string(book_id)  + "')";
    int ok = session->exec_into(q, id);
    if (ok != 0) {
        Logger::getInstance()->log(1, __FILE__, __LINE__, __TIME__,"impossible to take book!");
        throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                "impossible to take book!");
    }
    return std::vector<DBBook>();
}