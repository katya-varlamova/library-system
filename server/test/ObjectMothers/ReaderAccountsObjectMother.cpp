//
// Created by Екатерина on 23.11.2022.
//

#include "ReaderAccountsObjectMother.h"
std::vector<ReaderAccount> ReaderAccountsObjectMother::getDefault()
{
    std::shared_ptr<Account> a1 (new Account("l1", "p1", "admin", "ln1"));
    a1->setID(1);
    ReaderAccount aa1( a1, "123");
    aa1.setID(1);

    std::shared_ptr<Account> a2 (new Account("l2", "p2", "admin", "ln2"));
    a2->setID(2);
    ReaderAccount aa2(a2, "123");
    aa2.setID(2);

    std::shared_ptr<Account> a3 (new Account("l3", "p3", "admin", "ln3"));
    a3->setID(3);
    ReaderAccount aa3(a3, "123");
    aa3.setID(3);

    std::shared_ptr<Account> a4 (new Account("l4", "p4", "admin", "ln4"));
    a4->setID(4);
    ReaderAccount aa4(a4, "123");
    aa4.setID(4);

    std::shared_ptr<Account> a5 (new Account("l5", "p5", "admin", "ln5"));
    a5->setID(5);
    ReaderAccount aa5(a5, "123");
    aa5.setID(5);

    std::vector<ReaderAccount> accs = {aa1, aa2, aa3, aa4, aa5};
    return accs;
}

std::vector<ReaderAccount> ReaderAccountsObjectMother::getWithID(std::vector<ReaderAccount> accounts, int id) {
    std::vector<ReaderAccount> res;
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getAccount()->getID() == id)
            res.push_back(accounts[i]);
    }
    return res;
}
std::vector<ReaderAccount> ReaderAccountsObjectMother::getWithLogin(std::vector<ReaderAccount> accounts, std::string login)
{
    std::vector<ReaderAccount> res;
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getAccount()->getLogin() == login)
            res.push_back(accounts[i]);
    }
    return res;
}
std::vector<ReaderAccount> ReaderAccountsObjectMother::getWithUpd(std::vector<ReaderAccount> accounts, int id, ReaderAccount account)
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
std::vector<ReaderAccount> ReaderAccountsObjectMother::getWithAdd(std::vector<ReaderAccount> accounts, ReaderAccount account) {
    accounts.push_back(account);
    accounts[accounts.size() - 1].setID(accounts.size());
    return accounts;
}
std::vector<ReaderAccount> ReaderAccountsObjectMother::getWithDel(std::vector<ReaderAccount> accounts, int id)
{
    std::vector<ReaderAccount> res;
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getAccount()->getID() != id)
            res.push_back(accounts[i]);
    }
    return res;
}