//
// Created by Екатерина on 16.05.2022.
//

#ifndef SRC_IACCOUNTREPOSITORY_H
#define SRC_IACCOUNTREPOSITORY_H
class IAccountRepository {
public:
    virtual int addAccount(std::shared_ptr<Session> session, std::shared_ptr<Account> account) = 0;
    virtual void removeAccount(std::shared_ptr<Session> session, int id) = 0;
    virtual void updateAccount(std::shared_ptr<Session> session, std::shared_ptr<Account> account) = 0;

    virtual std::vector<std::shared_ptr<Account>> query(std::shared_ptr<Session> session, std::shared_ptr<AccountSpecification> specification) = 0;
};
#endif //SRC_IACCOUNTREPOSITORY_H
