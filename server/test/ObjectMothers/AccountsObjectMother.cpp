//
// Created by Екатерина on 21.11.2022.
//

#include "AccountsObjectMother.h"
std::vector<Account> AccountsObjectMother::getDefault()
{
    Account a1("l1", "p1", "reader", "ln1");
    a1.setID(1);

    Account a2("l2", "p2", "reader", "ln2");
    a2.setID(2);

    Account a3("l3", "p3", "librarian", "ln3");
    a3.setID(3);

    Account a4("l4", "p4", "librarian", "ln4");
    a4.setID(4);

    Account a5("l5", "p5", "admin", "ln5");
    a5.setID(5);

    std::vector<Account> accs = {a1, a2, a3, a4, a5};
    return accs;
}

std::vector<Account> AccountsObjectMother::getWithID(std::vector<Account> accounts, int id) {
    std::vector<Account> res;
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getID() == id)
            res.push_back(accounts[i]);
    }
    return res;
}
std::vector<Account> AccountsObjectMother::getWithLogin(std::vector<Account> accounts, std::string login)
{
    std::vector<Account> res;
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getLogin() == login)
            res.push_back(accounts[i]);
    }
    return res;
}
std::vector<Account> AccountsObjectMother::getWithUpd(std::vector<Account> accounts, int id, Account account)
{
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getID() == id) {
            accounts[i] = Account(account.getLogin(), account.getPassword(), account.getRole(), account.getName());
            accounts[i].setID(id);
        }
    }
    return accounts;
}
std::vector<Account> AccountsObjectMother::getWithAdd(std::vector<Account> accounts, Account account) {
    accounts.push_back(account);
    accounts[accounts.size() - 1].setID(accounts.size());
    return accounts;
}
std::vector<Account> AccountsObjectMother::getWithDel(std::vector<Account> accounts, int id)
{
    std::vector<Account> res;
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getID() != id)
            res.push_back(accounts[i]);
    }
    return res;
}