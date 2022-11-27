//
// Created by Екатерина on 10.04.2022.
//

#ifndef SRC_ADDBOOKSCOMMAND_H
#define SRC_ADDBOOKSCOMMAND_H

#include "DataAccessFacade/Commands/Command.h"
#include "../../../../Logic/Entities/Book/Book.h"
#include "Entities/DBBook/IBookRepository.h"
class AddBooksCommand : public Command{
public:
    AddBooksCommand( const std::shared_ptr<IBookRepository> &repository, const std::shared_ptr<ILibraryRepository> &lib_repository, const std::vector<std::shared_ptr<Book>> &books)
    {
        this->books = books;
        this->repository = repository;
        this->lib_repository = lib_repository;
    }
    void execute(std::shared_ptr<Session<>> session) override;

protected:
    std::shared_ptr<IBookRepository> repository;
    std::shared_ptr<ILibraryRepository> lib_repository;
    std::vector<std::shared_ptr<Book>> books;
};


#endif //SRC_ADDBOOKSCOMMAND_H
