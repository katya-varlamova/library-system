//
// Created by Екатерина on 23.05.2022.
//

#ifndef SRC_DBEBOOKMAPPINGS_H
#define SRC_DBEBOOKMAPPINGS_H
#include <string>
struct MappedEBook
{
    int id;
    int book_id;
    std::string link;
};

namespace soci
{
    template<>
    struct type_conversion<MappedEBook>
    {
        typedef values base_type;

        static void from_base(values const & v, indicator /* ind */, MappedEBook & b)
        {
            b.id = v.get<int>("id");
            b.book_id = v.get<int>("book_id");
            b.link = v.get<std::string>("link");
        }

        static void to_base(const MappedEBook & b, values & v, indicator & ind)
        {
            v.set("id", b.id);
            v.set("book_id", b.book_id);
            v.set("link", b.link);
            ind = i_ok;
        }
    };
}

#endif //SRC_DBEBOOKMAPPINGS_H
