//
// Created by Екатерина on 20.11.2022.
//

#ifndef SRC_BOOKSPECIFICATIONSTUB_H
#define SRC_BOOKSPECIFICATIONSTUB_H
#include "../Database/Entities/DBBook/BookSpecifications/BookSpecification.h"

class BookSpecificationStub : public BookSpecification {
public:
    BookSpecificationStub() = default;
    virtual std::vector<DBBook> exec(std::shared_ptr<Session<>> session) {
        session->exec("select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id where Library.id = 1 and author = 'auth1' and acc_id is NULL");
        DBBook dbbook;
        dbbook.set_book_id(1);
        dbbook.set_name("book1");
        dbbook.set_author("auth1");
        dbbook.set_lib_id(1);
        return std::vector<DBBook>({dbbook});
    }
};
#endif //SRC_BOOKSPECIFICATIONSTUB_H
