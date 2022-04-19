//
// Created by Екатерина on 29.03.2022.
//

#include "AuthCommand.h"
void AuthCommand::execute(soci::session & session) {
    AccountRepository repository;
    acc = repository.query(session, std::shared_ptr<AccountSpecification>(new GetAccountByLogin(login)));
}