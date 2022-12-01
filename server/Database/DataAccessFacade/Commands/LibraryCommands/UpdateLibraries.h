//
// Created by Екатерина on 11.05.2022.
//

#ifndef SRC_UPDATELIBRARIES_H
#define SRC_UPDATELIBRARIES_H


#include "DataAccessFacade/Commands/Command.h"
#include "../../../../Logic/Entities/Library/Library.h"
#include "Entities/DBLibrary/LibrarySpecifications/GetLibrary.h"
#include "Entities/DBLibrary/LibraryRepository.h"
class UpdateLibrariesCommand : public Command{
public:
    UpdateLibrariesCommand(std::shared_ptr<ILibraryRepository> repository, const std::shared_ptr<Library> &lib)
    { this->repository = repository; this->lib = lib;}
    void execute(std::shared_ptr<Session<>> session) override;

private:
    std::shared_ptr<Library> lib;
    std::shared_ptr<ILibraryRepository> repository;
};
#endif //SRC_UPDATELIBRARIES_H
