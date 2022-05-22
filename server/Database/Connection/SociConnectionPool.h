//
// Created by Екатерина on 22.05.2022.
//

#ifndef SRC_SOCICONNECTIONPOOL_H
#define SRC_SOCICONNECTIONPOOL_H

#include "IConnectionPool.h"
#include <string>
#include <soci/connection-pool.h>
#include <sqlite3.h>
#include <map>
#include <soci/session.h>
class SociConnectionPool : public IConnectionPool{
public:
    explicit SociConnectionPool(const std::vector<std::shared_ptr<IRoleConnection>> &conns): IConnectionPool(conns){}
    void connect() override;
    std::shared_ptr<Session> getConnectionByRole(const std::string &role, int &pos) override;
    void disconnect() override;
    void putConnectionByRole(const std::string &role, int pos) override;
private:
    bool registerRoleConnection(const std::string &role_name, unsigned max_role_connections, const std::string &conn_str);
    std::map<std::string, std::shared_ptr<soci::connection_pool>> pools;
    std::map<std::string, size_t> pool_sizes;
};


#endif //SRC_SOCICONNECTIONPOOL_H
