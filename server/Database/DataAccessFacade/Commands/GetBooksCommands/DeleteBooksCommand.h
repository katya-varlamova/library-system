//
// Created by Екатерина on 15.05.2022.
//

#ifndef SRC_DELETEBOOKSCOMMAND_H
#define SRC_DELETEBOOKSCOMMAND_H


#include "../Command.h"
#include "../../../Entities/DBBook/BookRepository.h"
class DeleteBooksCommand : public Command{
public:
    DeleteBooksCommand(int id)
    { this->id = id;}
    void execute(std::shared_ptr<Session> session) override;

private:
    int id;
};

#endif //SRC_DELETEBOOKSCOMMAND_H
