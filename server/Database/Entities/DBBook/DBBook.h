//
// Created by Екатерина on 27.03.2022.
//

#ifndef SRC_DBBOOK_H
#define SRC_DBBOOK_H

#include <soci/values.h>
#include <string>
#include "DBBookMappings.h"
class DBBook
{
public:
    MappedBook &get_mapped_book()
    {
        return mb;
    }
    MappedBookItem &get_mapped_book_item()
    {
        return mbi;
    };
    int get_item_id()
    {
        return mbi.id;
    }
    int get_book_id()
    {
        return mbi.book_id;
    }
    int get_lib_id()
    {
        return mbi.lib_id;
    }
    int get_acc_id()
    {
        return mbi.acc_id;
    }
    std::string get_name()
    {
        return mb.name;
    }
    std::string get_author()
    {
        return mb.author;
    }
    void set_item_id(int id)
    {
        mbi.id = id;
    }
    void set_book_id(int id)
    {
        mbi.book_id = id;
        mb.id = id;
    }
    void set_lib_id(int id)
    {
        mbi.lib_id = id;
    }
    void set_acc_id(int id)
    {
        mbi.acc_id = id;
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
    MappedBookItem mbi;
    MappedBook mb;
};

#endif //SRC_DBBOOK_H
