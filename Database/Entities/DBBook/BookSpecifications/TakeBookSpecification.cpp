//
// Created by Екатерина on 17.04.2022.
//

#include "TakeBookSpecification.h"
std::vector<DBBook> TakeBookSpecification::exec(soci::session &session)
{
    soci::indicator ind;
    int id;
    session << "select acc_id "
               "from BookItem "
               "where book_id = :book_id",
               soci::into(id, ind), soci::use(book_id);
    if (ind != soci::i_ok) {
        throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                "book has already been taken");
    }
    session << "update bookitem "
               "set acc_id = :acc_id "
               "where book_id = :book_id and id = "
               "(select min(id) "
               "from bookitem "
               "where acc_id is null and book_id = :book_id)",
               soci::use(book_id), soci::use(acc_id);
    return std::vector<DBBook>();
}