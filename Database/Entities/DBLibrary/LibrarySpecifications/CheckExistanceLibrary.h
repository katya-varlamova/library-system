//
// Created by Екатерина on 17.04.2022.
//

#ifndef SRC_CHECKEXISTANCELIBRARY_H
#define SRC_CHECKEXISTANCELIBRARY_H

#include "LibarySpecification.h"
class CheckExistanceLibrary : public LibarySpecification{
public:
    CheckExistanceLibrary(DBLibrary &library, bool &exist) : library(library), exist(exist)
    {}
    std::vector<DBLibrary> exec(soci::session &session) override;

protected:
    DBLibrary &library;
    bool &exist;
};


#endif //SRC_CHECKEXISTANCELIBRARY_H
