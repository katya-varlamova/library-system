//
// Created by Екатерина on 08.05.2022.
//

#include "GetBooks.h"
std::vector<DBBook> GetBooks::exec(std::shared_ptr<Session> session) {
    std::vector<DBBook> v_b;
    std::vector<MappedBookItem> bi;
    std::string fil_str;
    for (int i = 0; i < filters.size(); i++){
        if (i != filters.size() - 1)
            fil_str += filters[i]->getEqualClause() + " and ";
        else
            fil_str += filters[i]->getEqualClause();
    }
    std::string q_str;
    if (!filters.empty()) {
        q_str = "select BookItem.id, book_id, lib_id, acc_id "
                "from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id join Account on acc_id = Account.id "
                "where " + fil_str;
    }
    else
    {
        q_str = "select BookItem.id, book_id, lib_id, acc_id "
                "from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id join Account on acc_id = Account.id ";
    }
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