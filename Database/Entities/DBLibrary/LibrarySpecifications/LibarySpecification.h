//
// Created by Екатерина on 09.04.2022.
//

#ifndef SRC_LIBARYSPECIFICATION_H
#define SRC_LIBARYSPECIFICATION_H

#include <soci/session.h>
#include <libpq-fe.h>
#include <soci/soci.h>
#include "../DBLibrary.h"

class LibarySpecification {
public:
    LibarySpecification() = default;
    virtual std::vector<DBLibrary> exec(soci::session & session) = 0;
};


#endif //SRC_LIBARYSPECIFICATION_H
