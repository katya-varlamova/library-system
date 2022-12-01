//
// Created by Екатерина on 27.11.2022.
//

#include "LibrarianAccountRepositoryMock.h"

std::vector<std::shared_ptr<LibrarianAccount>> LibrarianAccountRepositoryMock::query(std::shared_ptr<Session<>> session,
                                                                   std::shared_ptr<LibrarianAccountSpecification> specification) {
    call_seq.push_back("query");
    if (!rv)
        return std::vector<std::shared_ptr<LibrarianAccount>>();
    LibrarianAccountsObjectMother objectMother;
    std::vector<LibrarianAccount> accs = objectMother.getDefault();
    std::vector<std::shared_ptr<LibrarianAccount>> paccs;
    for (auto l : accs)
    {
        std::shared_ptr<LibrarianAccount> acc(new LibrarianAccount(l));
        paccs.push_back(acc);
    }
    return paccs;
}
void LibrarianAccountRepositoryMock::addAccount(std::shared_ptr<Session<>> session,
                                                std::shared_ptr<LibrarianAccount> account){
    call_seq.push_back("add");
}
void LibrarianAccountRepositoryMock::updateAccount(std::shared_ptr<Session<>> session, std::shared_ptr<LibrarianAccount> account) {
    call_seq.push_back("update");
}
void LibrarianAccountRepositoryMock::removeAccount(std::shared_ptr<Session<>> session, int id)
{
    call_seq.push_back("remove");
}