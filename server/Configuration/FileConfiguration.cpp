//
// Created by Екатерина on 22.05.2022.
//

#include "FileConfiguration.h"
#include "../Logger/Logger.h"
void FileConfiguration::read()
{
    std::ifstream in;
    in.open(filename);

    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;
    Json::Value root;
    parseFromStream(builder, in, &root, &errs);
    rc = std::shared_ptr<ReaderRoleConnection>(new ReaderRoleConnection(root["reader"]["conn_str"].asString(),
                                                                        root["reader"]["max_conn"].asInt()));
    ac = std::shared_ptr<AdminRoleConnection>(new AdminRoleConnection(root["admin"]["conn_str"].asString(),
                                                                        root["admin"]["max_conn"].asInt()));
    lc = std::shared_ptr<LibrarianRoleConnection>(new LibrarianRoleConnection(root["librarian"]["conn_str"].asString(),
                                                                        root["librarian"]["max_conn"].asInt()));

    std::shared_ptr<Logger> l = Logger::getInstance();
    l->init(root["logger"]["level"].asInt(),
                 root["logger"]["filename"].asString().c_str());

    in.close();
}