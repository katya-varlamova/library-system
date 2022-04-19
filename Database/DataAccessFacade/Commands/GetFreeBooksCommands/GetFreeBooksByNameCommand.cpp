//
// Created by Екатерина on 04.04.2022.
//

#include "GetFreeBooksByNameCommand.h"

void GetFreeBooksByNameCommand::execute(soci::session &session)
{
    BookRepository repository;
    soci::transaction tr(session);
    books = repository.query(session, std::shared_ptr<BookSpecification>(new GetFreeBooksByNameSpec(name)));
    tr.commit();
}