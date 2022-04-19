//
// Created by Екатерина on 03.04.2022.
//

#ifndef SRC_BOOK_H
#define SRC_BOOK_H

#include <string>
#include "../Library/Library.h"
#include "../Account/Account.h"
class Book
{
public:
    Book(std::string name, std::string author, std::shared_ptr<Library> l)
    {
        this->name = name;
        this->author = author;
        this->library = l;
    }
    std::shared_ptr<Library> getLibrary()
    {
        return library;
    }
    std::string  getAuthor()
    {
        return author;
    }
    std::string  getName()
    {
        return name;
    }
private:
    std::string name;
    std::string author;
    std::shared_ptr<Library> library;
};


#endif //SRC_BOOK_H
