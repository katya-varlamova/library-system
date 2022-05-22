//
// Created by Екатерина on 09.04.2022.
//

#ifndef SRC_LIBRARYCONVERTER_H
#define SRC_LIBRARYCONVERTER_H

#include "../../../Logic/Entities/Library/Library.h"
#include "../DBLibrary/DBLibrary.h"

class LibraryConverter {
public:
    std::shared_ptr<Library> convert(DBLibrary library)
    {
        std::shared_ptr<Library> l(new Library(library.name, library.address));
        l->setID(library.id);
        return l;
    }
    DBLibrary convert(std::shared_ptr<Library> library)
    {
        DBLibrary lib;
        lib.id = library->getID();
        lib.name = library->getName();
        lib.address = library->getAddress();
        return lib;
    }
};


#endif //SRC_LIBRARYCONVERTER_H
