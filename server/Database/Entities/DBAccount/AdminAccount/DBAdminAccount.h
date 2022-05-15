//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_DBADMINACCOUNT_H
#define SRC_DBADMINACCOUNT_H
#include <string>
#include <libpq-fe.h>
#include <soci/values.h>
struct DBAdminAccount
{
    int id;
    int acc_id;
};

namespace soci
{
    template<>
    struct type_conversion<DBAdminAccount>
    {
        typedef values base_type;

        static void from_base(values const & v, indicator /* ind */, DBAdminAccount & a)
        {
            a.id = v.get<int>("id");
            a.acc_id = v.get<int>("acc_id");
        }

        static void to_base(const DBAdminAccount & a, values & v, indicator & ind)
        {
            v.set("id", a.id);
            v.set("acc_id", a.acc_id);
            ind = i_ok;
        }
    };
}
#endif //SRC_DBADMINACCOUNT_H
