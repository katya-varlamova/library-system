//
// Created by Екатерина on 15.05.2022.
//

#ifndef SRC_DELETELIBRARIESCOMMAND_H
#define SRC_DELETELIBRARIESCOMMAND_H

#include "../Command.h"
#include "../../../../Logic/Entities/Library/Library.h"
#include "../../../Entities/DBLibrary/LibrarySpecifications/GetLibrary.h"
#include "../../../Entities/DBLibrary/LibraryRepository.h"
class DeleteLibrariesCommand :public Command{
public:
    DeleteLibrariesCommand(int id)
    { this->id = id;}
    void execute(std::shared_ptr<Session> session) override;

private:
    int id;
};


#endif //SRC_DELETELIBRARIESCOMMAND_H
