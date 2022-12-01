//
// Created by Екатерина on 27.11.2022.
//

#include "AdminAccountRepositoryMock.h"
std::vector<std::shared_ptr<AdminAccount>> AdminAccountRepositoryMock::query(const std::shared_ptr<Session<>> &session,
                                                                             std::shared_ptr<AdminAccountSpecification> specification) {
    call_seq.push_back("query");
    if (!rv)
        return std::vector<std::shared_ptr<AdminAccount>>();
    AdminAccountsObjectMother objectMother;
    std::vector<AdminAccount> accs = objectMother.getDefault();
    std::vector<std::shared_ptr<AdminAccount>> paccs;
    for (auto l : accs)
    {
        std::shared_ptr<AdminAccount> acc(new AdminAccount(l));
        paccs.push_back(acc);
    }
    return paccs;
}
void AdminAccountRepositoryMock::addAccount(const std::shared_ptr<Session<>> &session,
                                            std::shared_ptr<AdminAccount> account) {
    call_seq.push_back("add");
}
void AdminAccountRepositoryMock::updateAccount(const std::shared_ptr<Session<>> &session,
                                               std::shared_ptr<AdminAccount> account) {
    call_seq.push_back("update");
}
void AdminAccountRepositoryMock::removeAccount(const std::shared_ptr<Session<>> &session, int id) {
    call_seq.push_back("remove");
}