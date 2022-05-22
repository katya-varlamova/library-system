//
// Created by Екатерина on 11.05.2022.
//

#ifndef SRC_POSTLIBRARIESCOMMAND_H
#define SRC_POSTLIBRARIESCOMMAND_H


#include "../Command.h"
#include "../../../../Logic/Entities/Library/Library.h"
#include "../../../Entities/DBLibrary/LibrarySpecifications/GetLibrary.h"
#include "../../../Entities/DBLibrary/LibraryRepository.h"
class PostLibrariesCommand : public Command{
public:
    PostLibrariesCommand(std::shared_ptr<ILibraryRepository> repository, const std::shared_ptr<Library> &lib)
    { this->repository = repository; this->lib = lib;}
    void execute(std::shared_ptr<Session> session) override;

private:
    std::shared_ptr<Library> lib;
    std::shared_ptr<ILibraryRepository> repository;
};

#endif //SRC_POSTLIBRARIESCOMMAND_H
