//
// Created by Екатерина on 03.04.2022.
//

#ifndef SRC_LIBRARY_H
#define SRC_LIBRARY_H
#include <string>

class Library {
public:
    Library(const std::string &name, const std::string &address)
    {
        this->name = name;
        this->address = address;
    }
    int getID() const
    {
        return id;
    }
    void setID(int id)
    {
        this->id = id;
    }
    std::string getName() const
    {
        return name;
    }
    std::string getAddress() const
    {
        return address;
    }
    bool operator == (const Library &l) const
    {
        return l.getID() == this->getID() && l.getName() == this->getName() && l.getAddress() == this->getAddress();
    }

private:
    int id;
    std::string name;
    std::string address;
};


#endif //SRC_LIBRARY_H
