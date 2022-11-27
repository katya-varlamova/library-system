//
// Created by Екатерина on 10.05.2022.
//

#include "ReturnBookSpecification.h"
#include "../../../../Logger/Logger.h"

std::vector<DBBook> ReturnBookSpecification::exec(std::shared_ptr<Session<>> session)
{
    int id;
    int ok = session->exec_into("select return_book('" + login_user +
                                   "', '" + login_lib +
                                   "', '" + std::to_string(book_id) + "')", id);
    if (ok != 0) {
        Logger::getInstance()->log(1, __FILE__, __LINE__, __TIME__,"impossible to return book!");
        throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                "impossible to return book!");
    }
    return std::vector<DBBook>();
}