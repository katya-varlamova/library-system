//
// Created by Екатерина on 23.05.2022.
//

#ifndef SRC_DBEBOOK_H
#define SRC_DBEBOOK_H
#include <string>
#include "../DBBook/DBBookMappings.h"
#include "DBEBookMappings.h"
class DBEBook
{
public:
    MappedBook &get_mapped_book()
    {
        return mb;
    }
    MappedEBook &get_mapped_ebook()
    {
        return meb;
    };
    int get_ebook_id()
    {
        return meb.id;
    }
    int get_book_id()
    {
        return meb.book_id;
    }
    std::string get_link()
    {
        return meb.link;
    }
    std::string get_name()
    {
        return mb.name;
    }
    std::string get_author()
    {
        return mb.author;
    }
    void set_ebook_id(int id)
    {
        meb.id = id;
    }
    void set_book_id(int id)
    {
        meb.book_id = id;
        mb.id = id;
    }
    void set_link(std::string link)
    {
        meb.link = link;
    }
    void set_name(const std::string &name)
    {
        mb.name = name;
    }
    void set_author(const std::string &author)
    {
        mb.author = author;
    }

protected:
    MappedEBook meb;
    MappedBook mb;
};
#endif //SRC_DBEBOOK_H
