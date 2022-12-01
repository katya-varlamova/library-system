//
// Created by Екатерина on 15.05.2022.
//

#ifndef SRC_DELETELIBRARIESCOMMAND_H
#define SRC_DELETELIBRARIESCOMMAND_H

#include "DataAccessFacade/Commands/Command.h"
#include "../../../../Logic/Entities/Library/Library.h"
#include "Entities/DBLibrary/LibrarySpecifications/GetLibrary.h"
#include "Entities/DBLibrary/LibraryRepository.h"
class DeleteLibrariesCommand :public Command{
public:
    DeleteLibrariesCommand(std::shared_ptr<ILibraryRepository> repository, int id)
    { this->repository = repository;
        this->id = id;}
    void execute(std::shared_ptr<Session<>> session) override;

private:
    int id;
    std::shared_ptr<ILibraryRepository> repository;
};


#endif //SRC_DELETELIBRARIESCOMMAND_H
