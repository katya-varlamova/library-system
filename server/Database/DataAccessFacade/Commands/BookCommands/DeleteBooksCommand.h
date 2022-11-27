//
// Created by Екатерина on 15.05.2022.
//

#ifndef SRC_DELETEBOOKSCOMMAND_H
#define SRC_DELETEBOOKSCOMMAND_H


#include "DataAccessFacade/Commands/Command.h"
#include "Entities/DBBook/IBookRepository.h"
class DeleteBooksCommand : public Command{
public:
    DeleteBooksCommand(std::shared_ptr<IBookRepository> repository, int id)
    { this->repository = repository;
        this->id = id;}
    void execute(std::shared_ptr<Session<>> session) override;

private:
    int id;
    std::shared_ptr<IBookRepository> repository;
};

#endif //SRC_DELETEBOOKSCOMMAND_H
