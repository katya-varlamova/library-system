//
// Created by Екатерина on 20.11.2022.
//

#include "LibrariesObjectMother.h"
std::vector<Library> LibrariesObjectMother::getDefault()
{
    Library l1("lib1", "addr1");
    l1.setID(1);

    Library l2("lib2", "addr2");
    l2.setID(2);

    Library l3("lib3", "addr3");
    l3.setID(3);

    Library l4("lib1", "addr2");
    l4.setID(4);

    Library l5("lib3", "addr2");
    l5.setID(5);

    std::vector<Library> libs = {l1, l2, l3, l4, l5};
    return libs;
}
std::vector<Library> LibrariesObjectMother::getWithName(std::vector<Library> libs, std::string name)
{
    std::vector<Library> res;
    for (int i = 0; i < libs.size(); i++)
    {
        if (libs[i].getName() == name)
            res.push_back(libs[i]);
    }
    return res;
}

std::vector<Library> LibrariesObjectMother::getWithAddress(std::vector<Library> libs, std::string address)
{
    std::vector<Library> res;
    for (int i = 0; i < libs.size(); i++)
    {
        if (libs[i].getAddress() == address)
            res.push_back(libs[i]);
    }
    return res;
}

std::vector<Library> LibrariesObjectMother::getWithID(std::vector<Library> libs, int id)
{
    std::vector<Library> res;
    for (int i = 0; i < libs.size(); i++)
    {
        if (libs[i].getID() == id)
            res.push_back(libs[i]);
    }
    return res;
}
std::vector<Library> LibrariesObjectMother::getWithAdd(std::vector<Library> libs, std::string name, std::string address)
{
    Library l(name, address);
    l.setID(libs.size() + 1);
    libs.push_back(l);
    return libs;
}

std::vector<Library> LibrariesObjectMother::getWithUpd(std::vector<Library> libs, int id, Library lib)
{
    for (int i = 0; i < libs.size(); i++)
    {
        if (libs[i].getID() == id) {
            libs[i] = Library(lib.getName(), lib.getAddress());
            libs[i].setID(id);
        }
    }
    return libs;
}

std::vector<Library> LibrariesObjectMother::getWithDel(std::vector<Library> libs, int id)
{
    std::vector<Library> res;
    for (int i = 0; i < libs.size(); i++)
    {
        if (libs[i].getID() != id) {
            res.push_back(libs[i]);
        }
    }
    return res;
}
