//
// Created by Екатерина on 09.04.2022.
//

#include "GetLibraryByID.h"
std::vector<DBLibrary> GetLibraryByID::exec(soci::session & session)
{
    std::vector<DBLibrary> v_lib;
    DBLibrary lib;
    soci::statement st = (session.prepare <<  "select * "
                                              "from public.Library"
                                              " where id = :id" , soci::into(lib), soci::use(id));
    st.execute();

    while (st.fetch())
        v_lib.push_back(lib);

    return v_lib;
}