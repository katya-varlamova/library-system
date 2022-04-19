//
// Created by Екатерина on 09.04.2022.
//

#include "GetFreeBooksByNameSpec.h"
std::vector<DBBook> GetFreeBooksByNameSpec::exec(soci::session & session)
{
    std::vector<DBBook> v_b;
    DBBook b;
    soci::statement st = (session.prepare <<  "select bi.id, bi.book_id, bi.lib_id, bi.acc_id "
                                              "from BookItem bi join Book b on bi.book_id = b.id "
                                              "where name = :name and acc_id is NULL",
                                              soci::into(b.get_mapped_book_item()),
                                              soci::use(name));
    st.execute();
    while (st.fetch()) {
        session <<  "select * from Book "
                    "where id = :id",
                soci::into(b.get_mapped_book()),
                soci::use(b.get_mapped_book_item().book_id);

        v_b.push_back(b);
    }

    return v_b;
}