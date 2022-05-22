//
// Created by Екатерина on 03.04.2022.
//

#ifndef SRC_LIBRARYREPOSITORY_H
#define SRC_LIBRARYREPOSITORY_H
#include <soci/rowset.h>
#include "DBLibrary.h"
#include "../../../Logic/Entities/Library/Library.h"
#include "LibrarySpecifications/LibarySpecification.h"
#include "LibrarySpecifications/GetLibrary.h"
#include "LibraryFilters/ByLibraryNameFilter.h"
#include "LibraryFilters/ByAddressFilter.h"
#include "LibraryConverter.h"
#include "ILibraryRepository.h"
class LibraryRepository : public ILibraryRepository{
public:
    int addLibrary(std::shared_ptr<Session> session, const std::shared_ptr<Library> &library);
    void removeLibrary(std::shared_ptr<Session> session, int id);
    void updateLibrary(std::shared_ptr<Session> session, std::shared_ptr<Library> library);

    std::vector<std::shared_ptr<Library>> query(std::shared_ptr<Session> session, std::shared_ptr<LibarySpecification> specification);
};



#endif //SRC_LIBRARYREPOSITORY_H
