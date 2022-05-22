//
// Created by Екатерина on 03.04.2022.
//

#ifndef SRC_DBLIBRARY_H
#define SRC_DBLIBRARY_H

#include <string>
#include <soci/values.h>

struct DBLibrary
{
    int id;
    std::string name;
    std::string address;
};

namespace soci
{
    template<>
    struct type_conversion<DBLibrary>
    {
        typedef values base_type;

        static void from_base(values const & v, indicator /* ind */, DBLibrary & b)
        {
            b.id = v.get<int>("id");
            b.name = v.get<std::string>("name");
            b.address = v.get<std::string>("address");
        }

        static void to_base(const DBLibrary & b, values & v, indicator & ind)
        {
            v.set("id", b.id);
            v.set("name", b.name);
            v.set("address", b.address);
            ind = i_ok;
        }
    };
}


#endif //SRC_DBLIBRARY_H
