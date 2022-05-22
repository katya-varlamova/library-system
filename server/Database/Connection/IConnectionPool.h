//
// Created by Екатерина on 29.03.2022.
//

#ifndef SRC_ICONNECTIONPOOL_H
#define SRC_ICONNECTIONPOOL_H
#include "Session.h"
#include "RoleConnection.h"
class IConnectionPool {
public:
    explicit IConnectionPool(const std::vector<std::shared_ptr<IRoleConnection>> &conns)
    {
        this->conns = conns;
    }
    virtual void connect() = 0;
    virtual std::shared_ptr<Session> getConnectionByRole(const std::string &role, int &pos) = 0;
    virtual void disconnect() = 0;
    virtual void putConnectionByRole(const std::string &role, int pos) = 0;

protected:
    std::vector<std::shared_ptr<IRoleConnection>> conns;
};


#endif //SRC_ICONNECTIONPOOL_H
