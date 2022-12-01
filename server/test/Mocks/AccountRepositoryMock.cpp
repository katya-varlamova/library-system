//
// Created by Екатерина on 27.11.2022.
//

#include "AccountRepositoryMock.h"
std::vector<std::shared_ptr<Account>> AccountRepositoryMock::query(std::shared_ptr<Session<>> session,
                                                                   std::shared_ptr<AccountSpecification> specification) {
    call_seq.push_back("query");
    if (!rv)
        return std::vector<std::shared_ptr<Account>>();
    AccountsObjectMother objectMother;
    std::vector<Account> accs = objectMother.getDefault();
    std::vector<std::shared_ptr<Account>> paccs;
    for (auto l : accs)
    {
        std::shared_ptr<Account> acc(new Account(l));
        paccs.push_back(acc);
    }
    return paccs;
}
int AccountRepositoryMock::addAccount(std::shared_ptr<Session<>> session, std::shared_ptr<Account> account) 
{ 
    call_seq.push_back("add");
    return rv;
}
void AccountRepositoryMock::updateAccount(std::shared_ptr<Session<>> session, std::shared_ptr<Account> account) {
    call_seq.push_back("update");
}
void AccountRepositoryMock::removeAccount(std::shared_ptr<Session<>> session, int id) 
{
    call_seq.push_back("remove");
}