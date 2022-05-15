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
    PostLibrariesCommand(const std::shared_ptr<Library> &lib)
    { this->lib = lib;}
    void execute(std::shared_ptr<Session> session) override;

private:
    std::shared_ptr<Library> lib;
};

#endif //SRC_POSTLIBRARIESCOMMAND_H
