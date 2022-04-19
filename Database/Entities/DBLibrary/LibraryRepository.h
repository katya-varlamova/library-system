//
// Created by Екатерина on 03.04.2022.
//

#ifndef SRC_LIBRARYREPOSITORY_H
#define SRC_LIBRARYREPOSITORY_H
#include <soci/rowset.h>
#include "DBLibrary.h"
#include "../../../Logic/Entities/Library/Library.h"
#include "LibrarySpecifications/LibarySpecification.h"
#include "LibrarySpecifications/CheckExistanceLibrary.h"
#include "LibraryConverter.h"
class LibraryRepository {
public:
    void addLibrary(soci::session & session, const std::shared_ptr<Library> &library);
    void removeLibrary(soci::session & session, std::shared_ptr<Library> library);
    void updateLibrary(soci::session & session, std::shared_ptr<Library> library);

    std::vector<std::shared_ptr<Library>> query(soci::session & session, std::shared_ptr<LibarySpecification> specification);
};



#endif //SRC_LIBRARYREPOSITORY_H
