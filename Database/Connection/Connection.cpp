//
// Created by Екатерина on 29.03.2022.
//

#include "Connection.h"
bool Connection::registerRoleConnection(const std::string &role_name, unsigned int max_role_connections, const std::string &conn_str)
{
    if (pools.find(role_name) != pools.end())
        return false;

    pools[role_name] = std::shared_ptr<soci::connection_pool>(new soci::connection_pool(max_role_connections));
    pool_sizes[role_name] = max_role_connections;

    for (int i = 0; i < max_role_connections; i++) {
        soci::session& s = pools[role_name]->at(i);
        s.open(conn_str);
    }
    return true;
}
std::shared_ptr<Session> Connection::getConnectionByRole(const std::string &role, int &pos)
{
    auto it = pools.find(role);
    pos = pools[role]->lease();
    return std::shared_ptr<Session>(new Session(pools[role]->at(pos)));
}
void Connection::putConnectionByRole(const std::string &role, int pos)
{
    pools[role]->give_back(pos);
}
void Connection::disconnect()
{
    auto size = pool_sizes.begin();
    for (auto pool = pools.begin(); pool != pools.end(); pool++, size++) {
        if (pool->second != nullptr) {
            for (std::size_t i = 0; i < size->second; i++) {
                soci::session &s = pool->second->at(i);
                s.close();
            }
        }
    }
}