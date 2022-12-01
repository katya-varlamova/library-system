//
// Created by Екатерина on 20.11.2022.
//

#ifndef SRC_LIBRARYSPECIFICATIONSTUB_H
#define SRC_LIBRARYSPECIFICATIONSTUB_H
#include "../Database/Entities/DBLibrary/LibrarySpecifications/LibarySpecification.h"

class LibrarySpecificationStub : public LibarySpecification{
public:
    LibrarySpecificationStub() = default;
    virtual std::vector<DBLibrary> exec(std::shared_ptr<Session<>> session) {
        session->exec("select * from Library where Library.id = 1");
        DBLibrary dblib;
        dblib.id = 1;
        dblib.name = "lib1";
        dblib.address = "addr1";
        return std::vector<DBLibrary>({dblib});
    }
};


#endif //SRC_LIBRARYSPECIFICATIONSTUB_H
