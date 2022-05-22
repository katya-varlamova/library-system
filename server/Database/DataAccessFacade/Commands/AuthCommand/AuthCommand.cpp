//
// Created by Екатерина on 29.03.2022.
//

#include "AuthCommand.h"

void AuthCommand::execute(std::shared_ptr<Session> session) {
    std::vector<std::shared_ptr<AccountFilter>> filters = { std::shared_ptr<AccountFilter>(new ByLoginFilter(login))};
    acc = repository->query(session, std::shared_ptr<AccountSpecification>(new GetAccount(filters)));
}