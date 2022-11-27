//
// Created by Екатерина on 27.11.2022.
//

#ifndef SRC_READERACCOUNTREPOSITORYMOCK_H
#define SRC_READERACCOUNTREPOSITORYMOCK_H

#include "Entities/DBAccount/ReaderAccount/IReaderAccountRepository.h"
#include "../ObjectMothers/ReaderAccountsObjectMother.h"
class ReaderAccountRepositoryMock : public IReaderAccountRepository{
public:
    ReaderAccountRepositoryMock(bool rv){
        this->rv = rv;
    }
    void addAccount(std::shared_ptr<Session<>> session, std::shared_ptr<ReaderAccount> account) override;
    void removeAccount(std::shared_ptr<Session<>> session, int id) override;
    std::vector<std::shared_ptr<ReaderAccount>> query(std::shared_ptr<Session<>> session, std::shared_ptr<ReaderAccountSpecification> specification) override;
    void updateAccount(std::shared_ptr<Session<>> session, std::shared_ptr<ReaderAccount> account) override;
    std::vector<std::string> getSequence()
    {
        return call_seq;
    }
private:
    bool rv;
    std::vector<std::string> call_seq;
};

#endif //SRC_READERACCOUNTREPOSITORYMOCK_H
