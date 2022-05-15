//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_DBREADERACCOUNT_H
#define SRC_DBREADERACCOUNT_H
#include <string>
#include <libpq-fe.h>
#include <soci/values.h>
struct DBReaderAccount
{
    int id;
    int acc_id;
    std::string phone;
};

namespace soci
{
    template<>
    struct type_conversion<DBReaderAccount>
    {
        typedef values base_type;

        static void from_base(values const & v, indicator /* ind */, DBReaderAccount & a)
        {
            a.id = v.get<int>("id");
            a.acc_id = v.get<int>("acc_id");
            a.phone = v.get<std::string>("phone");
        }

        static void to_base(const DBReaderAccount & a, values & v, indicator & ind)
        {
            v.set("id", a.id);
            v.set("phone", a.phone);
            v.set("acc_id", a.acc_id);
            ind = i_ok;
        }
    };
}
#endif //SRC_DBREADERACCOUNT_H
