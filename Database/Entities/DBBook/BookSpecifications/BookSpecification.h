//
// Created by Екатерина on 03.04.2022.
//

#ifndef SRC_BOOKSPECIFICATION_H
#define SRC_BOOKSPECIFICATION_H


#include "../DBBook.h"
#include <soci/session.h>
#include <libpq-fe.h>
#include <soci/soci.h>
#include "../../../DatabseException.h"
class BookSpecification
{
public:
    BookSpecification() = default;
    virtual std::vector<DBBook> exec(soci::session & session) = 0;
};



#endif //SRC_BOOKSPECIFICATION_H
