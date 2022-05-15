//
// Created by Екатерина on 17.04.2022.
//

#ifndef SRC_DBBOOKMAPPINGS_H
#define SRC_DBBOOKMAPPINGS_H
#include <soci/values.h>
#include <string>
struct MappedBook
{
    int id;
    std::string name;
    std::string author;
};

namespace soci
{
    template<>
    struct type_conversion<MappedBook>
    {
        typedef values base_type;

        static void from_base(values const & v, indicator /* ind */, MappedBook & b)
        {
            b.id = v.get<int>("id");
            b.name = v.get<std::string>("name");
            b.author = v.get<std::string>("author");
        }

        static void to_base(const MappedBook & b, values & v, indicator & ind)
        {
            v.set("id", b.id);
            v.set("name", b.name);
            v.set("author", b.author);
            ind = i_ok;
        }
    };
}

struct MappedBookItem
{
    int id;
    int book_id;
    int lib_id;
    int acc_id;
};

namespace soci
{
    template<>
    struct type_conversion<MappedBookItem>
    {
        typedef values base_type;

        static void from_base(values const & v, indicator /* ind */, MappedBookItem & b)
        {
            b.id = v.get<int>("id");
            b.book_id = v.get<int>("book_id");
            b.lib_id = v.get<int>("lib_id");
            b.acc_id = v.get<int>("acc_id", -1);
        }

        static void to_base(const MappedBookItem & b, values & v, indicator & ind)
        {
            v.set("id", b.id);
            v.set("book_id", b.book_id);
            v.set("lib_id", b.lib_id);
            v.set("acc_id", b.acc_id);
            ind = i_ok;
        }
    };
}

#endif //SRC_DBBOOKMAPPINGS_H
