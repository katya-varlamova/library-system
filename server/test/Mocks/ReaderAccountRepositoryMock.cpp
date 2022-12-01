//
// Created by Екатерина on 27.11.2022.
//

#include "ReaderAccountRepositoryMock.h"
std::vector<std::shared_ptr<ReaderAccount>> ReaderAccountRepositoryMock::query(std::shared_ptr<Session<>> session,
                                                                                     std::shared_ptr<ReaderAccountSpecification> specification) {
    call_seq.push_back("query");
    if (!rv)
        return std::vector<std::shared_ptr<ReaderAccount>>();
    ReaderAccountsObjectMother objectMother;
    std::vector<ReaderAccount> accs = objectMother.getDefault();
    std::vector<std::shared_ptr<ReaderAccount>> paccs;
    for (auto l : accs)
    {
        std::shared_ptr<ReaderAccount> acc(new ReaderAccount(l));
        paccs.push_back(acc);
    }
    return paccs;
}
void ReaderAccountRepositoryMock::addAccount(std::shared_ptr<Session<>> session,
                                                std::shared_ptr<ReaderAccount> account){
    call_seq.push_back("add");
}
void ReaderAccountRepositoryMock::updateAccount(std::shared_ptr<Session<>> session, std::shared_ptr<ReaderAccount> account) {
    call_seq.push_back("update");
}
void ReaderAccountRepositoryMock::removeAccount(std::shared_ptr<Session<>> session, int id)
{
    call_seq.push_back("remove");
}