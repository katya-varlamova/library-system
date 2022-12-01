//
// Created by Екатерина on 23.11.2022.
//

#include "LibrarianAccountsObjectMother.h"
std::vector<LibrarianAccount> LibrarianAccountsObjectMother::getDefault()
{
    std::shared_ptr<Account> a1 (new Account("l1", "p1", "admin", "ln1"));
    a1->setID(1);
    LibrarianAccount aa1( a1, 3);
    aa1.setID(1);

    std::shared_ptr<Account> a2 (new Account("l2", "p2", "admin", "ln2"));
    a2->setID(2);
    LibrarianAccount aa2(a2, 2);
    aa2.setID(2);

    std::shared_ptr<Account> a3 (new Account("l3", "p3", "admin", "ln3"));
    a3->setID(3);
    LibrarianAccount aa3(a3, 1);
    aa3.setID(3);

    std::shared_ptr<Account> a4 (new Account("l4", "p4", "admin", "ln4"));
    a4->setID(4);
    LibrarianAccount aa4(a4, 1);
    aa4.setID(4);

    std::shared_ptr<Account> a5 (new Account("l5", "p5", "admin", "ln5"));
    a5->setID(5);
    LibrarianAccount aa5(a5, 2);
    aa5.setID(5);

    std::vector<LibrarianAccount> accs = {aa1, aa2, aa3, aa4, aa5};
    return accs;
}

std::vector<LibrarianAccount> LibrarianAccountsObjectMother::getWithID(std::vector<LibrarianAccount> accounts, int id) {
    std::vector<LibrarianAccount> res;
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getAccount()->getID() == id)
            res.push_back(accounts[i]);
    }
    return res;
}
std::vector<LibrarianAccount> LibrarianAccountsObjectMother::getWithLogin(std::vector<LibrarianAccount> accounts, std::string login)
{
    std::vector<LibrarianAccount> res;
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getAccount()->getLogin() == login)
            res.push_back(accounts[i]);
    }
    return res;
}
std::vector<LibrarianAccount> LibrarianAccountsObjectMother::getWithUpd(std::vector<LibrarianAccount> accounts, int id, LibrarianAccount account)
{
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getAccount()->getID() == id) {
            int tid = accounts[i].getID();
            accounts[i] = account;
            accounts[i].setID(tid);
        }
    }
    return accounts;
}
std::vector<LibrarianAccount> LibrarianAccountsObjectMother::getWithAdd(std::vector<LibrarianAccount> accounts, LibrarianAccount account) {
    accounts.push_back(account);
    accounts[accounts.size() - 1].setID(accounts.size());
    return accounts;
}
std::vector<LibrarianAccount> LibrarianAccountsObjectMother::getWithDel(std::vector<LibrarianAccount> accounts, int id)
{
    std::vector<LibrarianAccount> res;
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getAccount()->getID() != id)
            res.push_back(accounts[i]);
    }
    return res;
}