//
// Created by Екатерина on 03.04.2022.
//

#include "Account.h"
Account::Account(const std::string &login, const std::string &password, const std::string &role, const std::string &name)
{
    this->name = name;
    this->login = login;
    this->role = role;
    this->password = password;
}
std::string Account::getPassword()
{
    return password;
}
std::string Account::getLogin()
{
    return login;
}
std::string Account::getRole()
{
    return role;
}
std::string Account::getName()
{
    return name;
}
