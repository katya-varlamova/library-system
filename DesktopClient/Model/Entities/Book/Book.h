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
    Book(const std::string &name, const std::string &author, int lib_id = -1, const std::string &login = "")
    {
        this->name = name;
        this->author = author;
        this->lib_id = lib_id;
        this->login = login;
    }
    int getLibraryID()
    {
        return lib_id;
    }
    std::string  getLogin()
    {
        return login;
    }
    std::string  getAuthor()
    {
        return author;
    }
    std::string  getName()
    {
        return name;
    }
    int getID()
    {
        return id;
    }
    void setID(int id)
    {
        this->id = id;
    }
private:
    int id;
    int lib_id;
    std::string name;
    std::string author;
    std::string login;
};


#endif //SRC_BOOK_H
