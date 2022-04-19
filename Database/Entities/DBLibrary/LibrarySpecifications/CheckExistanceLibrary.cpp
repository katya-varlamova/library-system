//
// Created by Екатерина on 17.04.2022.
//

#include "CheckExistanceLibrary.h"

std::vector<DBLibrary> CheckExistanceLibrary::exec(soci::session &session)
{
    exist = false;
    DBLibrary l;
    std::string name = library.name, address = library.address;
    session <<  "select * "
                "from public.Library "
                "where name = :name and address = :address" ,
                soci::into(l),
                soci::use(name),
                soci::use(address);
    if (session.got_data()) {
        exist = true;
        library = l;
    }
    return std::vector({library});
}