//
// Created by Екатерина on 03.04.2022.
//

#ifndef SRC_ACCOUNT_H
#define SRC_ACCOUNT_H
#include <string>

class Account {
public:
    Account(const std::string &login, const std::string &password, const std::string &role, const std::string &name);
    std::string getLogin() const;
    std::string getPassword() const;
    std::string getRole() const ;
    std::string getName() const;
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
