//
// Created by Екатерина on 20.11.2022.
//

#ifndef SRC_BOOKSOBJECTMOTHER_H
#define SRC_BOOKSOBJECTMOTHER_H


#include "../Logic/Entities/Book/Book.h"
#include <vector>
class BooksObjectMother {
public:
    std::vector<Book> getDefault();
    std::vector<Book> getWithName(std::vector<Book> books,  std::string name);
    std::vector<Book> getWithAuthor(std::vector<Book> books,  std::string author);
    std::vector<Book> getWithLogin(std::vector<Book> books,  std::string login);
    std::vector<Book> getWithID(std::vector<Book> books, int id);
    std::vector<Book> getWithLibID(std::vector<Book> books, int lid);
    std::vector<Book> getWithAdd(std::vector<Book> books, Book book);
    std::vector<Book> getWithDel(std::vector<Book> books, int id);
    std::vector<Book> getWithUpd(std::vector<Book> books, int id, Book book);
};


#endif //SRC_BOOKSOBJECTMOTHER_H
