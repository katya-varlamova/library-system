//
// Created by Екатерина on 21.05.2022.
//

#ifndef INTERFACE_CONSOLEPRESENTER_H
#define INTERFACE_CONSOLEPRESENTER_H

#include <iostream>
#include "../Model/Entities/Account/Account.h"
#include "../Model/Model.h"
#include "ConsoleView.h"
class ConsolePresenter {
public:
    ConsolePresenter(std::shared_ptr<Model> model)
    {
        this->model = model;
    }
    void run();

private:
    std::shared_ptr<Account> login();
    void registration();
    void workReader(const std::string &login, const std::string &pass);
    void workAdmin(const std::string &login, const std::string &pass);
    void workLibrarian(const std::string &login, const std::string &pass);
    std::shared_ptr<AdminAccount> regAdmin();
    std::shared_ptr<LibrarianAccount> regLibrarian();
    std::shared_ptr<ReaderAccount> regReader();
    void printAllLibs(const std::string &login, const std::string &pass);
    void printAllBooks(const std::string &login, const std::string &pass);
    void updateBook(const std::string &login, const std::string &pass);
    void deleteBook(const std::string &login, const std::string &pass);
    void addBook(const std::string &login, const std::string &pass);
    void updateLibrary(const std::string &login, const std::string &pass);
    void deleteLibrary(const std::string &login, const std::string &pass);
    void addLibrary(const std::string &login, const std::string &pass);
    std::shared_ptr<Account>  inputAccount(const std::string &role);
    std::shared_ptr<Model> model;
    void giveBook(const std::string &login, const std::string &pass);
    void returnBook(const std::string &login, const std::string &pass);
    ConsoleView view;
};

#endif //INTERFACE_CONSOLEPRESENTER_H
