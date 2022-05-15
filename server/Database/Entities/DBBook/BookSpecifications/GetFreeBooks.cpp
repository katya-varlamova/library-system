//
// Created by Екатерина on 08.05.2022.
//

#include <unistd.h>
#include "GetFreeBooks.h"
std::vector<DBBook> GetFreeBooks::exec(std::shared_ptr<Session> session)
{
    std::vector<DBBook> v_b;
    std::vector<MappedBookItem> bi;
    std::string fil_str;
    bool is_login;
    for (auto &f: filters)
        fil_str += f->getEqualClause() + " and ";
    std::string q_str = "select BookItem.id, book_id, lib_id, acc_id "
                        "from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id "
                        "where ";
    q_str += fil_str + "acc_id is NULL";
    session->exec_into(q_str, bi);
    for (auto &book_item : bi) {
        MappedBook mb;
        session->exec_into(std::string("select * from Book "
                                  "where id = ") + std::to_string(book_item.book_id),
                      mb);
        DBBook book;
        book.get_mapped_book_item() = book_item;
        book.get_mapped_book() = mb;
        v_b.push_back(book);
    }
    return v_b;
}