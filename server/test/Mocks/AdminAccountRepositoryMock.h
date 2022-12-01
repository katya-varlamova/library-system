//
// Created by Екатерина on 27.11.2022.
//

#ifndef SRC_ADMINACCOUNTREPOSITORYMOCK_H
#define SRC_ADMINACCOUNTREPOSITORYMOCK_H

#include "Entities/DBAccount/AdminAccount/IAdminAccountRepository.h"
#include "../ObjectMothers/AdminAccountsObjectMother.h"
class AdminAccountRepositoryMock : public IAdminAccountRepository{
public:
    AdminAccountRepositoryMock(bool rv){
        this->rv = rv;
    }
    void addAccount(const std::shared_ptr<Session<>> &session, std::shared_ptr<AdminAccount> account) override;
    void removeAccount(const std::shared_ptr<Session<>> &session, int id) override;
    void updateAccount(const std::shared_ptr<Session<>> &session, std::shared_ptr<AdminAccount> account) override;
    std::vector<std::shared_ptr<AdminAccount>> query(const std::shared_ptr<Session<>> &session, std::shared_ptr<AdminAccountSpecification> specification) override;
    std::vector<std::string> getSequence()
    {
        return call_seq;
    }
private:
    bool rv;
    std::vector<std::string> call_seq;
};

#endif //SRC_ADMINACCOUNTREPOSITORYMOCK_H
