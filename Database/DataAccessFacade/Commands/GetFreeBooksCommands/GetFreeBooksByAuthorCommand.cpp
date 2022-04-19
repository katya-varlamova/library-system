//
// Created by Екатерина on 10.04.2022.
//

#include "GetFreeBooksByAuthorCommand.h"

void GetFreeBooksByAuthorCommand::execute(soci::session &session)
{
    BookRepository repository;
    soci::transaction tr(session);
    books = repository.query(session, std::shared_ptr<BookSpecification>(new GetFreeBooksByAuthorSpec(author)));
    tr.commit();
}