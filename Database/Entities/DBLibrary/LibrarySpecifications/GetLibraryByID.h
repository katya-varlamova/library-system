//
// Created by Екатерина on 09.04.2022.
//

#ifndef SRC_GETLIBRARYBYID_H
#define SRC_GETLIBRARYBYID_H

#include "LibarySpecification.h"
class GetLibraryByID : public LibarySpecification{
public:
    GetLibraryByID(int id)
    {
        this->id = id;
    }
    std::vector<DBLibrary> exec(soci::session & session) override;

protected:
    int id;
};


#endif //SRC_GETLIBRARYBYID_H
