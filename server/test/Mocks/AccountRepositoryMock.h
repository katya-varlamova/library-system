//
// Created by Екатерина on 27.11.2022.
//

#ifndef SRC_ACCOUNTREPOSITORYMOCK_H
#define SRC_ACCOUNTREPOSITORYMOCK_H

#include <Connection/Session.h>
#include <Entities/DBAccount/AccountSpecifications/AccountSpecification.h>
#include "Entities/DBAccount/IAccountRepository.h"
#include "../ObjectMothers/AccountsObjectMother.h"
class AccountRepositoryMock : public IAccountRepository{
public:
    AccountRepositoryMock(bool rv){
        this->rv = rv;
    }
    int addAccount(std::shared_ptr<Session<>> session, std::shared_ptr<Account> account) override;
    void removeAccount(std::shared_ptr<Session<>> session, int id) override;
    void updateAccount(std::shared_ptr<Session<>> session, std::shared_ptr<Account> account) override;
    std::vector<std::shared_ptr<Account>> query(std::shared_ptr<Session<>> session, std::shared_ptr<AccountSpecification> specification) override;
    std::vector<std::string> getSequence()
    {
        return call_seq;
    }
private:
    bool rv;
    std::vector<std::string> call_seq;
};


#endif //SRC_ACCOUNTREPOSITORYMOCK_H
