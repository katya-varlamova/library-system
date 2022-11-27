//
// Created by Екатерина on 20.11.2022.
//

#ifndef SRC_TESTINGSESSION_H
#define SRC_TESTINGSESSION_H

#include <string>
#include <map>
#include <vector>
#include "../Logic/Entities/Library/Library.h"
#include "ObjectMothers/LibrariesObjectMother.h"
#include "../Logic/Entities/Book/Book.h"
#include "../Logic/Entities/Account/AdminAccount.h"
#include "../Logic/Entities/Account/ReaderAccount.h"
#include "../Logic/Entities/Account/LibrarianAccount.h"

class TestingSession {
public:
    TestingSession() = default;
    void initLibraryTable(const std::vector<Library> &table)
    {
        this->libTable = table;
    }
    std::vector<Library> getSelectedLibraryTable()
    {
        return selectedLibTable;
    }

    void initBookTable(const std::vector<Book> &table)
    {
        this->bookTable = table;
    }
    std::vector<Book> getSelectedBookTable()
    {
        return selectedBookTable;
    }

    void initAccountTable(const std::vector<Account> &table)
    {
        this->accountTable = table;
    }
    std::vector<Account> getSelectedAccountTable()
    {
        return selectedAccountTable;
    }

    void initAdminAccountTable(const std::vector<AdminAccount> &table)
    {
        this->adminAccountTable = table;
    }
    std::vector<AdminAccount> getSelectedAdminAccountTable()
    {
        return selectedAdminAccountTable;
    }

    void initReaderAccountTable(const std::vector<ReaderAccount> &table)
    {
        this->readerAccountTable = table;
    }
    std::vector<ReaderAccount> getSelectedReaderAccountTable()
    {
        return selectedReaderAccountTable;
    }

    void initLibrarianAccountTable(const std::vector<LibrarianAccount> &table)
    {
        this->librarianAccountTable = table;
    }
    std::vector<LibrarianAccount> getSelectedLibrarianAccountTable()
    {
        return selectedLibrarianAccountTable;
    }
    void analyze(const std::string &query);

private:
    std::vector<Library> libTable;
    std::vector<Library> selectedLibTable;

    std::vector<Book> bookTable;
    std::vector<Book> selectedBookTable;

    std::vector<Account> accountTable;
    std::vector<Account> selectedAccountTable;

    std::vector<AdminAccount> adminAccountTable;
    std::vector<AdminAccount> selectedAdminAccountTable;

    std::vector<ReaderAccount> readerAccountTable;
    std::vector<ReaderAccount> selectedReaderAccountTable;

    std::vector<LibrarianAccount> librarianAccountTable;
    std::vector<LibrarianAccount> selectedLibrarianAccountTable;
};


#endif //SRC_TESTINGSESSION_H
