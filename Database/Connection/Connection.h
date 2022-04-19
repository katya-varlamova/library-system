//
// Created by Екатерина on 29.03.2022.
//

#ifndef SRC_CONNECTION_H
#define SRC_CONNECTION_H
#include <string>
#include <soci/connection-pool.h>
#include <map>
#include <soci/session.h>
class Connection {
public:
    Connection() = default;
    bool registerRoleConnection(const std::string &role_name, unsigned max_role_connections, const std::string &conn_str);
    soci::session & getConnectionByRole(const std::string &role, int &pos);
    void disconnect();
    void putConnectionByRole(const std::string &role, int pos);
private:
    std::map<std::string, std::shared_ptr<soci::connection_pool>> pools;
    std::map<std::string,size_t> pool_sizes;
};


#endif //SRC_CONNECTION_H
