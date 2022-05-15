//
// Created by Екатерина on 27.03.2022.
//

#ifndef SRC_DBACCOUNT_H
#define SRC_DBACCOUNT_H

#include <string>
#include <libpq-fe.h>
#include <soci/values.h>
struct DBAccount
{
    int id;
    std::string login;
    std::string password;
    std::string role;
    std::string name;
};

namespace soci
{
    template<>
    struct type_conversion<DBAccount>
    {
        typedef values base_type;

        static void from_base(values const & v, indicator /* ind */, DBAccount & a)
        {
            a.id = v.get<int>("id");
            a.login = v.get<std::string>("login");
            a.password = v.get<std::string>("password");
            a.role = v.get<std::string>("role");
            a.name = v.get<std::string>("name");
        }

        static void to_base(const DBAccount & a, values & v, indicator & ind)
        {
            v.set("id", a.id);
            v.set("login", a.login);
            v.set("password", a.password);
            v.set("role", a.role);
            v.set("name", a.name);
            ind = i_ok;
        }
    };
}


#endif //SRC_DBACCOUNT_H
