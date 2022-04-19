//
// Created by Екатерина on 10.04.2022.
//

#include "AddBooksCommand.h"
#include "../../../Entities/DBBook/BookRepository.h"

void AddBooksCommand::execute(soci::session &session)
{
    BookRepository repository;

    for (int i = 0; i < books.size(); i++) {
        soci::transaction tr(session);
        repository.addBook(session, books[i]);
        tr.commit();
    }
}