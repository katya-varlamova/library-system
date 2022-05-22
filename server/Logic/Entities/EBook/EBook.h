//
// Created by Екатерина on 23.05.2022.
//

#ifndef SRC_EBOOK_H
#define SRC_EBOOK_H

#include <string>
class EBook {
public:
    EBook(const std::string &name, const std::string &author, const std::string &link)
    {
        this->name = name;
        this->author = author;
        this->link = link;
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
    std::string getLink()
    {
        return link;
    }
    void setLink(const std::string &link)
    {
        this->link = link;
    }
private:
    int id;
    std::string link;
    std::string name;
    std::string author;
};

#endif //SRC_EBOOK_H
