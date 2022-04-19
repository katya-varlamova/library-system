//
// Created by Екатерина on 03.04.2022.
//

#ifndef SRC_ACCOUNT_H
#define SRC_ACCOUNT_H
#include <string>

class Account {
public:
    Account(const std::string &login, const std::string &password, const std::string &role, const std::string &name);
    std::string getLogin();
    std::string getPassword();
    std::string getRole();
    std::string getName();
private:
    std::string login;
    std::string password;
    std::string role;
    std::string name;
};

#endif //SRC_ACCOUNT_H
