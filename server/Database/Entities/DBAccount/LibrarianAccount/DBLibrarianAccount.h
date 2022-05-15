//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_DBLIBRARIANACCOUNT_H
#define SRC_DBLIBRARIANACCOUNT_H
#include <string>
#include <libpq-fe.h>
#include <soci/values.h>
struct DBLibrarianAccount
{
    int id;
    int acc_id;
    int lib_id;
};

namespace soci
{
    template<>
    struct type_conversion<DBLibrarianAccount>
    {
        typedef values base_type;

        static void from_base(values const & v, indicator /* ind */, DBLibrarianAccount & a)
        {
            a.id = v.get<int>("id");
            a.acc_id = v.get<int>("acc_id");
            a.lib_id = v.get<int>("lib_id");
        }

        static void to_base(const DBLibrarianAccount & a, values & v, indicator & ind)
        {
            v.set("id", a.id);
            v.set("lib_id", a.lib_id);
            v.set("acc_id", a.acc_id);
            ind = i_ok;
        }
    };
}
#endif //SRC_DBLIBRARIANACCOUNT_H
