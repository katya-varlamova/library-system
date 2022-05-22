//
// Created by Екатерина on 21.05.2022.
//

#include "ConsolePresenter.h"
void ConsolePresenter::run()
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    view.outputString("Please, choose:\n0. exit \n1. login\n2. registration\n");
    int num;
    do {
        view.outputString("Choise: ");
        std:: cin >> num;

        if (num == 1) {
            std::shared_ptr<Account> acc = login();
            if (acc->getRole() == "reader")
                workReader(acc->getLogin(), acc->getPassword());
            if (acc->getRole() == "admin")
                workAdmin(acc->getLogin(), acc->getPassword());
            if (acc->getRole() == "librarian")
                workLibrarian(acc->getLogin(), acc->getPassword());
            view.outputString("Please, choose:\n0. exit \n1. login\n2. registration\n");
        } else if (num == 2)
        {
            registration();
            view.outputString("Please, choose:\n0. exit \n1. login\n2. registration\n");
        }
        else if (num != 0)
        {
            view.outputString("Incorrect!");
        }
    }
    while (num != 0);
}

std::shared_ptr<Account> ConsolePresenter::login()
{
    bool got = false;
    std::shared_ptr<Account> acc;
    std::string log, pass;
    char *buf = (char *) malloc(70);
    do {
        view.inputString("Login: ", log);
        view.inputString("Password: ", pass);
        acc = model->login(log, pass);
        if (acc)
            got = true;
        else
            view.outputString("Failed! Try again:\n");
    } while (!got);
    return acc;
}
std::shared_ptr<Account> ConsolePresenter::inputAccount(const std::string &role)
{
    std::string log, pass, name;
    view.inputString("login: ", log);
    view.inputString("password: ", pass);
    view.inputString("name: ", name);
    return std::shared_ptr<Account>(new Account(log, pass, role, name));
}
std::shared_ptr<AdminAccount> ConsolePresenter::regAdmin()
{
    return std::shared_ptr<AdminAccount> (new AdminAccount(inputAccount("admin")));
}
std::shared_ptr<LibrarianAccount> ConsolePresenter::regLibrarian()
{
    auto libs = model->getLibraries("admin", "admin");
    int i =0;
    for (auto &lib : libs)
    {
        view.outputString(std::to_string(i + 1) + ". library name: " + lib->getName() +
                     " library address: " + lib->getAddress() + "\n");
        i++;
    }
    int num;
    view.inputNum("choose: ", num);
    while (num >= libs.size()){ view.inputNum("choose: ", num);}
    return std::shared_ptr<LibrarianAccount> (new LibrarianAccount(inputAccount("librarian"), libs[num - 1]->getID()));
}
std::shared_ptr<ReaderAccount> ConsolePresenter::regReader()
{
    std::string phone;
    view.inputString("phone: ", phone);
    return std::shared_ptr<ReaderAccount> (new ReaderAccount(inputAccount("reader"), phone));

}
void ConsolePresenter::registration()
{
    int num;
    view.outputString("Exit: 0\nChoose role:\n1. Admin\n2. Librarian\n3. Reader\n");
    do {
        view.inputNum("choose: ", num);
        if (num == 1)
        {
            std::shared_ptr<AdminAccount> acc = regAdmin();
            int i = model->registration(acc);
            if (i != 0)
                std:: cout << "failed";
            num = 0;
        } else if (num == 2)
        {
            std::shared_ptr<LibrarianAccount> acc = regLibrarian();
            int i = model->registration(acc);
            if (i != 0)
                std:: cout << "failed";
            num = 0;
        } else if (num == 3)
        {
            std::shared_ptr<ReaderAccount> acc = regReader();
            int i = model->registration(acc);
            if (i != 0)
                std:: cout << "failed";
            num = 0;
        } else if (num != 0)
        {
            std:: cout << "incorrect choise!\n";
        }
    } while (num != 0);
}
void ConsolePresenter::printAllLibs(const std::string &login, const std::string &pass)
{
    auto libs = model->getLibraries(login, pass);
    for (auto &lib : libs)
        view.outputString("id: " + std::to_string(lib->getID()) + " name: " + lib->getName() + " address:" + lib->getAddress() + "\n");
}
void ConsolePresenter::printAllBooks(const std::string &login, const std::string &pass)
{
    auto books = model->getBooks(login, pass);
    for (auto &book : books)
        view.outputString("id: " + std::to_string(book->getID())
        + " name: " + book->getName()
        + " author: " + book->getAuthor()
        + " user login: " + book->getLogin()
        + " library id: " + std::to_string(book->getLibraryID()) + "\n");

}
void ConsolePresenter::updateBook(const std::string &login, const std::string &pass)
{
    int id, lib_id;
    view.inputNum("id: ", id);
    view.inputNum("library id: ", lib_id);
    std::string name, author;
    view.inputString("book name: ", name);
    view.inputString("book author: ", author);
    auto b = std::shared_ptr<Book>(new Book(name, author, lib_id));
    b->setID(id);
    model->updateBook(login, pass, b);
}
void ConsolePresenter::deleteBook(const std::string &login, const std::string &pass)
{
    int id;
    view.inputNum("book id: ", id);
    model->deleteBook(login, pass, id);
}
void ConsolePresenter::addBook(const std::string &login, const std::string &pass)
{
    int lib_id;
    view.inputNum("library id: ", lib_id);
    std::string name, author;
    view.inputString("book name: ", name);
    view.inputString("book author: ", author);
    model->addBook(login, pass, std::shared_ptr<Book>(new Book(name, author, lib_id)));
}
void ConsolePresenter::updateLibrary(const std::string &login, const std::string &pass)
{
    int id;
    view.inputNum("id: ", id);
    std::string name, address;
    view.inputString("library name: ", name);
    view.inputString("library address: ", address);
    auto l = std::shared_ptr<Library>(new Library(name, address));
    l->setID(id);
    model->updateLibrary(login, pass, l);
}
void ConsolePresenter::deleteLibrary(const std::string &login, const std::string &pass)
{
    int id;
    view.inputNum("library id: ", id);
    model->deleteLibrary(login, pass, id);
}
void ConsolePresenter::addLibrary(const std::string &login, const std::string &pass)
{
    std::string name, address;
    view.inputString("library name: ", name);
    view.inputString("library address: ", address);
    model->addLibrary(login, pass, std::shared_ptr<Library>(new Library(name, address)));
}
void ConsolePresenter::workAdmin(const std::string &login, const std::string &pass)
{
    view.outputString("0. exit\n"
                 "1. print libs\n"
                 "2. print books\n"
                 "3. update book\n"
                 "4. update library\n"
                 "5. delete book\n"
                 "6. delete library\n"
                 "7. add book\n"
                 "8. add library\n");
    int num = -1;

    do
    {
        view.inputNum("choise: ", num);
        switch (num) {
            case 1: {
                printAllLibs(login, pass);
                break;
            }
            case 2: {
                printAllBooks(login, pass);
                break;
            }
            case 3:
            {
                updateBook(login, pass);
                break;
            }
            case 4: {
                updateLibrary(login, pass);
                break;
            }
            case 5:
            {
                deleteBook(login, pass);
                break;
            }
            case 6: {
                deleteLibrary(login, pass);
                break;
            }
            case 7:
            {
                addBook(login, pass);
                break;
            }
            case 8:
            {
                addLibrary(login, pass);
                break;
            }
            default: {
                if (num != 0)
                    view.outputString("incorrect choise!\n");
            }

        }
    } while (num != 0);
}
void ConsolePresenter::giveBook(const std::string &login, const std::string &pass)
{
    std::string log;
    int id;
    view.inputNum("book id: ", id);
    view.inputString("user login: ", log);
    model->giveBook(login, pass, log, id);
}
void ConsolePresenter::returnBook(const std::string &login, const std::string &pass)
{
    std::string log;
    int id;
    view.inputNum("book id: ", id);
    view.inputString("user login: ", log);
    model->returnBook(login, pass, log, id);
}
void ConsolePresenter::workLibrarian(const std::string &login, const std::string &pass)
{
    view.outputString("0. exit\n"
                 "1. print books\n"
                 "2. give book\n"
                 "3. return library\n");
    int num = -1;

    do
    {
        view.inputNum("choise: ", num);
        switch (num) {
            case 1: {
                printAllBooks(login, pass);
                break;
            }
            case 2: {
                giveBook(login, pass);
                break;
            }
            case 3:
            {
                returnBook(login, pass);
                break;
            }
            default: {
                if (num != 0)
                    view.outputString("incorrect choise!\n");
            }

        }
    } while (num != 0);

}
void ConsolePresenter::workReader(const std::string &login, const std::string &pass)
{
    view.outputString("0. exit\n"
                 "1. print books\n");
    int num = -1;

    do
    {
        view.inputNum("choise: ", num);
        switch (num) {
            case 1: {
                printAllBooks(login, pass);
                break;
            }
            default: {
                if (num != 0)
                    view.outputString("incorrect choise!\n");
            }

        }
    } while (num != 0);
}