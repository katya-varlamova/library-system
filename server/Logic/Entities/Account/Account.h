//
// Created by Екатерина on 03.04.2022.
//

#ifndef SRC_ACCOUNT_H
#define SRC_ACCOUNT_H
#include <string>
#include <memory>
class Account {
public:
    Account(const std::string &login, const std::string &password, const std::string &role, const std::string &name)
    {
        this->name = name;
        this->login = login;
        this->role = role;
        this->password = password;
    }
    std::string getPassword() const
    {
        return password;
    }
    std::string getLogin() const
    {
        return login;
    }
    std::string getRole() const
    {
        return role;
    }
    std::string getName() const
    {
        return name;
    }

    int getID() const
    {
        return id;
    }
    void setID(int id)
    {
        this->id = id;
    }
    bool operator == (const Account &l) const
    {
        return l.getID() == this->getID() &&
               l.getName() == this->getName() &&
               l.getPassword() == this->getPassword() &&
               l.getLogin() == this->getLogin() &&
               l.getRole() == this->getRole();
    }
private:
    int id;
    std::string login;
    std::string password;
    std::string role;
    std::string name;
};

#endif //SRC_ACCOUNT_H
