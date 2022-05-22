//
// Created by Екатерина on 16.05.2022.
//

#ifndef SRC_ILIBRARYREPOSITORY_H
#define SRC_ILIBRARYREPOSITORY_H
#include <soci/rowset.h>
#include "DBLibrary.h"
#include "../../../Logic/Entities/Library/Library.h"
#include "LibrarySpecifications/LibarySpecification.h"
#include "LibrarySpecifications/GetLibrary.h"
#include "LibraryFilters/ByLibraryNameFilter.h"
#include "LibraryFilters/ByAddressFilter.h"
#include "LibraryConverter.h"
#include "ILibraryRepository.h"
class ILibraryRepository {
public:
    virtual int addLibrary(std::shared_ptr<Session> session, const std::shared_ptr<Library> &library) = 0;
    virtual void removeLibrary(std::shared_ptr<Session> session, int id) = 0;
    virtual void updateLibrary(std::shared_ptr<Session> session, std::shared_ptr<Library> library)=  0;

    virtual std::vector<std::shared_ptr<Library>> query(std::shared_ptr<Session> session, std::shared_ptr<LibarySpecification> specification) = 0;
};


#endif //SRC_ILIBRARYREPOSITORY_H
