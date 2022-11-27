//
// Created by Екатерина on 11.05.2022.
//

#ifndef SRC_GETLIBRARIESCOMMAND_H
#define SRC_GETLIBRARIESCOMMAND_H


#include "../Command.h"
#include "../../../../Logic/Entities/Library/Library.h"
#include "../../../Entities/DBLibrary/LibrarySpecifications/GetLibrary.h"
#include "../../../Entities/DBLibrary/LibraryRepository.h"
class GetlibrariesCommand : public Command{
public:
    GetlibrariesCommand(std::shared_ptr<ILibraryRepository> repository, std::vector<std::shared_ptr<Library>> &libs, std::vector<std::shared_ptr<LibraryFilter>> &filters)
            : libs(libs) { this->repository = repository; this->filters = filters;}
    void execute(std::shared_ptr<Session<>> session) override;

private:
    std::shared_ptr<ILibraryRepository> repository;
    std::vector<std::shared_ptr<Library>> &libs;
    std::vector<std::shared_ptr<LibraryFilter>> filters;
};

#endif //SRC_GETLIBRARIESCOMMAND_H
