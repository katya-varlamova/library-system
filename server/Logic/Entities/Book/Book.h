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
    int getLibraryID() const
    {
        return lib_id;
    }
    std::string  getAuthor() const
    {
        return author;
    }
    std::string  getName() const
    {
        return name;
    }
    int getID() const
    {
        return id;
    }
    void setID(int id)
    {
        this->id = id;
    }
    std::string  getLogin() const
    {
        return login;
    }
    bool operator == (const Book &l) const
    {
        return l.getID() == this->getID() &&
        l.getName() == this->getName() &&
        l.getAuthor() == this->getAuthor() &&
        l.getLogin() == this->getLogin() &&
        l.getLibraryID() == this->getLibraryID();
    }
private:
    int id;
    int lib_id;
    std::string login;
    std::string name;
    std::string author;
};


#endif //SRC_BOOK_H
