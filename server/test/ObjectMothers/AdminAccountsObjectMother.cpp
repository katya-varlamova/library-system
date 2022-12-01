//
// Created by Екатерина on 21.11.2022.
//

#include "AdminAccountsObjectMother.h"
std::vector<AdminAccount> AdminAccountsObjectMother::getDefault()
{
    std::shared_ptr<Account> a1 (new Account("l1", "p1", "admin", "ln1"));
    a1->setID(1);
    AdminAccount aa1(a1);
    aa1.setID(1);

    std::shared_ptr<Account> a2 (new Account("l2", "p2", "admin", "ln2"));
    a2->setID(2);
    AdminAccount aa2(a2);
    aa2.setID(2);

    std::shared_ptr<Account> a3 (new Account("l3", "p3", "admin", "ln3"));
    a3->setID(3);
    AdminAccount aa3(a3);
    aa3.setID(3);

    std::shared_ptr<Account> a4 (new Account("l4", "p4", "admin", "ln4"));
    a4->setID(4);
    AdminAccount aa4(a4);
    aa4.setID(4);

    std::shared_ptr<Account> a5 (new Account("l5", "p5", "admin", "ln5"));
    a5->setID(5);
    AdminAccount aa5(a5);
    aa5.setID(5);

    std::vector<AdminAccount> accs = {aa1, aa2, aa3, aa4, aa5};
    return accs;
}

std::vector<AdminAccount> AdminAccountsObjectMother::getWithID(std::vector<AdminAccount> accounts, int id) {
    std::vector<AdminAccount> res;
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getAccount()->getID() == id)
            res.push_back(accounts[i]);
    }
    return res;
}
std::vector<AdminAccount> AdminAccountsObjectMother::getWithLogin(std::vector<AdminAccount> accounts, std::string login)
{
    std::vector<AdminAccount> res;
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getAccount()->getLogin() == login)
            res.push_back(accounts[i]);
    }
    return res;
}
std::vector<AdminAccount> AdminAccountsObjectMother::getWithUpd(std::vector<AdminAccount> accounts, int id, AdminAccount account)
{
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getAccount()->getID() == id) {
            accounts[i] = account;
            accounts[i].setID(id);
        }
    }
    return accounts;
}
std::vector<AdminAccount> AdminAccountsObjectMother::getWithAdd(std::vector<AdminAccount> accounts, AdminAccount account) {
    accounts.push_back(account);
    accounts[accounts.size() - 1].setID(accounts.size());
    return accounts;
}
std::vector<AdminAccount> AdminAccountsObjectMother::getWithDel(std::vector<AdminAccount> accounts, int id)
{
    std::vector<AdminAccount> res;
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getAccount()->getID() != id)
            res.push_back(accounts[i]);
    }
    return res;
}