//
// Created by Екатерина on 27.11.2022.
//

#ifndef SRC_LIBRARIANLibrarianAccountREPOSITORYMOCK_H
#define SRC_LIBRARIANLibrarianAccountREPOSITORYMOCK_H

#include "Entities/DBAccount/LibrarianAccount/ILibrarianAccountRepository.h"
#include "../ObjectMothers/LibrarianAccountsObjectMother.h"
class LibrarianAccountRepositoryMock : public ILibrarianAccountRepository{
public:
    LibrarianAccountRepositoryMock(bool rv){
        this->rv = rv;
    }
    void addAccount(std::shared_ptr<Session<>> session, std::shared_ptr<LibrarianAccount> account) override;
    void removeAccount(std::shared_ptr<Session<>> session, int id) override;
    std::vector<std::shared_ptr<LibrarianAccount>> query(std::shared_ptr<Session<>> session, std::shared_ptr<LibrarianAccountSpecification> specification) override;
    void updateAccount(std::shared_ptr<Session<>> session, std::shared_ptr<LibrarianAccount> account) override;
    std::vector<std::string> getSequence()
    {
        return call_seq;
    }
private:
    bool rv;
    std::vector<std::string> call_seq;
};


#endif //SRC_LIBRARIANLibrarianAccountREPOSITORYMOCK_H
