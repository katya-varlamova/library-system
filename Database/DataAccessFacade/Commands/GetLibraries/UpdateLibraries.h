//
// Created by Екатерина on 11.05.2022.
//

#ifndef SRC_UPDATELIBRARIES_H
#define SRC_UPDATELIBRARIES_H


#include "../Command.h"
#include "../../../../Logic/Entities/Library/Library.h"
#include "../../../Entities/DBLibrary/LibrarySpecifications/GetLibrary.h"
#include "../../../Entities/DBLibrary/LibraryRepository.h"
class UpdateLibrariesCommand : public Command{
public:
    UpdateLibrariesCommand(const std::shared_ptr<Library> &lib)
    { this->lib = lib;}
    void execute(std::shared_ptr<Session> session) override;

private:
    std::shared_ptr<Library> lib;
};
#endif //SRC_UPDATELIBRARIES_H
