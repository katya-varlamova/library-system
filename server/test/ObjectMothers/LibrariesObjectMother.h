//
// Created by Екатерина on 20.11.2022.
//

#ifndef SRC_LIBRARIESOBJECTMOTHER_H
#define SRC_LIBRARIESOBJECTMOTHER_H

#include "../Logic/Entities/Library/Library.h"
#include <vector>
class LibrariesObjectMother {
public:
    std::vector<Library> getDefault();
    std::vector<Library> getWithName(std::vector<Library> libs,  std::string name);
    std::vector<Library> getWithAddress(std::vector<Library> libs,  std::string address);
    std::vector<Library> getWithID(std::vector<Library> libs, int id);
    std::vector<Library> getWithAdd(std::vector<Library> libs, std::string name, std::string address);
    std::vector<Library> getWithDel(std::vector<Library> libs, int id);
    std::vector<Library> getWithUpd(std::vector<Library> libs, int id, Library lib);
};


#endif //SRC_LIBRARIESOBJECTMOTHER_H
