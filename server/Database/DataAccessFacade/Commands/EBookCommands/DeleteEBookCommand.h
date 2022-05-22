//
// Created by Екатерина on 23.05.2022.
//

#ifndef SRC_DELETEEBOOK_H
#define SRC_DELETEEBOOK_H
#include "../Command.h"
#include "../../../Entities/DBEBook/IEBookRepository.h"
#include "../../../../Logger/Logger.h"
class DeleteEBooksCommand : public Command{
public:
    DeleteEBooksCommand(std::shared_ptr<IEBookRepository> repository, int id)
    { this->repository = repository;
        this->id = id;}
    void execute(std::shared_ptr<Session> session) override
    {
        session->begin_transaction();
        repository->removeBook(session, id);
        session->commit_transaction();
        Logger::getInstance()->log(4, __FILE__, __LINE__, __TIME__,"ebook was removed!");
    }


private:
    int id;
    std::shared_ptr<IEBookRepository> repository;
};
#endif //SRC_DELETEEBOOK_H
