//
// Created by Екатерина on 22.05.2022.
//

#ifndef SRC_ROLECONNECTION_H
#define SRC_ROLECONNECTION_H
class IRoleConnection{
public:
    std::string getConnectionString()
    {
        return conn_str;
    }
    int getMaxConnection()
    {
        return max;
    }
    virtual std::string getRoleString() = 0;
protected:
    std::string conn_str;
    int max;
};
class AdminRoleConnection : public IRoleConnection{
public:
    AdminRoleConnection(const std::string &conn_str, int max)
    {
        this->conn_str = conn_str;
        this->max = max;
    }
    std::string getRoleString() override
    {
        return "admin";
    }
};
class ReaderRoleConnection : public IRoleConnection{
public:
    ReaderRoleConnection(const std::string &conn_str, int max)
    {
        this->conn_str = conn_str;
        this->max = max;
    }
    std::string getRoleString() override
    {
        return "reader";
    }
};
class LibrarianRoleConnection : public IRoleConnection{
public:
    LibrarianRoleConnection(const std::string &conn_str, int max)
    {
        this->conn_str = conn_str;
        this->max = max;
    }
    std::string getRoleString() override
    {
        return "librarian";
    }
};
#endif //SRC_ROLECONNECTION_H
