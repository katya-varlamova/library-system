//
// Created by Екатерина on 23.05.2022.
//

#include "GetEBooksSpecification.h"
std::vector<DBEBook> GetEBooksSpecification::exec(std::shared_ptr<Session<>> session) {
    std::vector<DBEBook> v_b;
    std::vector<MappedEBook> eb;
    std::string fil_str;
    for (int i = 0; i < filters.size(); i++){
        if (i != filters.size() - 1)
            fil_str += filters[i]->getEqualClause() + " and ";
        else
            fil_str += filters[i]->getEqualClause();
    }
    std::string q_str;
    if (!filters.empty()) {
        q_str = "select EBook.id, book_id, link "
                "from EBook join Book on book_id = Book.id "
                "where " + fil_str;
    }
    else
    {
        q_str = "select EBook.id, book_id, link "
                "from EBook join Book on book_id = Book.id ";
    }
    session->exec_into(q_str, eb);
    for (auto &book_item : eb) {
        MappedBook mb;
        session->exec_into(std::string("select * from Book "
                                       "where id = ") + std::to_string(book_item.book_id),
                           mb);
        DBEBook book;
        book.get_mapped_ebook() = book_item;
        book.get_mapped_book() = mb;
        v_b.push_back(book);
    }
    return v_b;
}