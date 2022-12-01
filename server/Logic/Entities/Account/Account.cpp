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
std::string Account::getPassword() const
{
    return password;
}
std::string Account::getLogin() const
{
    return login;
}
std::string Account::getRole() const
{
    return role;
}
std::string Account::getName() const
{
    return name;
}
