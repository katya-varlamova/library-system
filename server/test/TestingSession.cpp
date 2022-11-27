//
// Created by Екатерина on 20.11.2022.
//

#include "TestingSession.h"
#include "ObjectMothers/BooksObjectMother.h"
#include "ObjectMothers/AccountsObjectMother.h"
#include "ObjectMothers/AdminAccountsObjectMother.h"
#include "ObjectMothers/ReaderAccountsObjectMother.h"
#include "ObjectMothers/LibrarianAccountsObjectMother.h"

void TestingSession::analyze(const std::string &query) {
    // printf("%s\n", query.c_str());

    if (query == "select * from Library where Library.name = 'lib1'"){
        LibrariesObjectMother objectMother;
        selectedLibTable = objectMother.getWithName(libTable, "lib1");
    }
    if (query == "select * from Library where address = 'addr2'"){
        LibrariesObjectMother objectMother;
        selectedLibTable = objectMother.getWithAddress(libTable, "addr2");
    }
    if (query == "select * from Library where Library.id = 1"){
        LibrariesObjectMother objectMother;
        selectedLibTable = objectMother.getWithID(libTable, 1);
    }
    if (query == "insert into Library (name, address) values('name', 'address');")
    {
        LibrariesObjectMother objectMother;
        selectedLibTable = objectMother.getWithAdd(libTable, "name", "address");
    }
    if (query == "update Library set name = 'uplib1', address = 'upaddr1' where id = 1")
    {
        LibrariesObjectMother objectMother;
        Library l("uplib1", "upaddr1");
        l.setID(1);
        selectedLibTable = objectMother.getWithUpd(libTable, 1, l);
    }
    if (query == "delete from Library where id = 1")
    {
        LibrariesObjectMother objectMother;
        selectedLibTable = objectMother.getWithDel(libTable, 1);
    }
    if (query == "select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id left join Account on acc_id = Account.id where Book.name = 'book1'"){
        BooksObjectMother objectMother;
        selectedBookTable = objectMother.getWithName(bookTable, "book1");
    }
    if (query == "select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id left join Account on acc_id = Account.id where author = 'auth1'")
    {
        BooksObjectMother objectMother;
        selectedBookTable = objectMother.getWithAuthor(bookTable, "auth1");
    }
    if (query == "select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id left join Account on acc_id = Account.id where Library.id = 1")
    {
        BooksObjectMother objectMother;
        selectedBookTable = objectMother.getWithLibID(bookTable, 1);
    }
    if (query == "select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id left join Account on acc_id = Account.id where Bookitem.id = 1")
    {
        BooksObjectMother objectMother;
        selectedBookTable = objectMother.getWithID(bookTable, 1);
    }
    if (query == "select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id left join Account on acc_id = Account.id where login = 'user'")
    {
        BooksObjectMother objectMother;
        selectedBookTable = objectMother.getWithLogin(bookTable, "user");
    }
    if (query == "select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id left join Account on acc_id = Account.id where login = 'user' and author = 'auth2'")
    {
        BooksObjectMother objectMother;
        selectedBookTable = objectMother.getWithLogin(objectMother.getWithAuthor(bookTable, "auth2"), "user");

    }
    if (query == "select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id where Book.name = 'book1' and acc_id is NULL")
    {
        BooksObjectMother objectMother;
        selectedBookTable = objectMother.getWithLogin(objectMother.getWithName(bookTable, "book1"), "");
    }
    if (query == "select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id where author = 'auth1' and acc_id is NULL")
    {
        BooksObjectMother objectMother;
        selectedBookTable = objectMother.getWithLogin(objectMother.getWithAuthor(bookTable, "auth1"), "");
    }
    if (query == "select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id where Library.id = 1 and acc_id is NULL")
    {
        BooksObjectMother objectMother;
        selectedBookTable = objectMother.getWithLogin(objectMother.getWithLibID(bookTable, 1), "");
    }
    if (query == "select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id where Bookitem.id = 1 and acc_id is NULL")
    {
        BooksObjectMother objectMother;
        selectedBookTable = objectMother.getWithLogin(objectMother.getWithID(bookTable, 1), "");
    }
    if (query == "select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id where Library.id = 1 and author = 'auth1' and acc_id is NULL")
    {
        BooksObjectMother objectMother;
        selectedBookTable = objectMother.getWithLogin(objectMother.getWithLibID(objectMother.getWithAuthor(bookTable, "auth1"), 1), "");

    }
    if (query == "insert into BookItem (book_id, lib_id, acc_id) values(1, 3, NULL)")
    {
        BooksObjectMother objectMother;
        Book b("book1", "auth1", 3);
        selectedBookTable = objectMother.getWithAdd(bookTable, b);
    }
    if (query == "update Book set name = 'updb1', author = 'upda1' where id = (select max(Book.id) from Book join Bookitem on book_id = Book.id where Bookitem.id = 1)")
    {
        BooksObjectMother objectMother;
        Book b("updb1", "upda1");
        selectedBookTable = objectMother.getWithUpd(bookTable, 1, b);
    }
    if (query == "update BookItem set lib_id = 2 where id = 1")
    {
        BooksObjectMother objectMother;
        Book b("updb1", "upda1", 2);
        selectedBookTable = objectMother.getWithUpd(bookTable, 1, b);
    }
    if (query == "delete from BookItem where id = 1")
    {
        BooksObjectMother objectMother;
        selectedBookTable = objectMother.getWithDel(bookTable, 1);
    }
    if (query == "select * from Account where Account.id = 1")
    {
        AccountsObjectMother objectMother;
        selectedAccountTable = objectMother.getWithID(accountTable, 1);
    }
    if (query == "select * from Account where login = 'l1'")
    {
        AccountsObjectMother objectMother;
        selectedAccountTable = objectMother.getWithLogin(accountTable, "l1");
    }
    if (query == "insert into Account (login, password, name, role) values('l6', 'p6', 'n6', 'admin');")
    {
        AccountsObjectMother objectMother;
        Account account("l6", "p6", "admin", "n6");
        selectedAccountTable = objectMother.getWithAdd(accountTable, account);
    }
    if (query == "update Account set login = 'l6', password = 'p6',name = 'n6' where id = 5")
    {
        AccountsObjectMother objectMother;
        Account account("l6", "p6", "admin", "n6");
        account.setID(5);
        selectedAccountTable = objectMother.getWithAdd(accountTable, account);

        AdminAccountsObjectMother accountsObjectMother;
        AdminAccount adminAccount(std::shared_ptr<Account>(new Account(account)));
        selectedAdminAccountTable = accountsObjectMother.getWithUpd(adminAccountTable, 5, adminAccount);
    }
    if (query == "delete from Account where id = 1")
    {
        AccountsObjectMother objectMother;
        selectedAccountTable = objectMother.getWithDel(accountTable, 1);
    }
    if (query == "select AdminAccount.id, AdminAccount.acc_id from Account join AdminAccount on AdminAccount.acc_id = Account.id where Account.id = 1")
    {
        AdminAccountsObjectMother objectMother;
        selectedAdminAccountTable = objectMother.getWithID(adminAccountTable, 1);
    }
    if (query == "select AdminAccount.id, AdminAccount.acc_id from Account join AdminAccount on AdminAccount.acc_id = Account.id where login = 'l1'")
    {
        AdminAccountsObjectMother objectMother;
        selectedAdminAccountTable = objectMother.getWithLogin(adminAccountTable, "l1");
    }
    if (query == "insert into AdminAccount (acc_id) values( '1')")
    {
        if (!selectedAccountTable.empty()) {
            AdminAccountsObjectMother accountsObjectMother;
            AdminAccount adminAccount(std::shared_ptr<Account>(new Account(selectedAccountTable[selectedAccountTable.size() - 1])));
            selectedAdminAccountTable = accountsObjectMother.getWithAdd(adminAccountTable, adminAccount);
        }
    }
    if (query == "delete from AdminAccount where acc_id = 5")
    {
        AdminAccountsObjectMother accountsObjectMother;
        selectedAdminAccountTable = accountsObjectMother.getWithDel(adminAccountTable, 5);
    }
    if (query == "select ReaderAccount.id, ReaderAccount.acc_id, phone from Account join ReaderAccount on ReaderAccount.acc_id = Account.id where Account.id = 1")
    {
        ReaderAccountsObjectMother objectMother;
        selectedReaderAccountTable = objectMother.getWithID(readerAccountTable, 1);
    }
    if (query == "select ReaderAccount.id, ReaderAccount.acc_id, phone from Account join ReaderAccount on ReaderAccount.acc_id = Account.id where login = 'l1'")
    {
        ReaderAccountsObjectMother objectMother;
        selectedReaderAccountTable = objectMother.getWithLogin(readerAccountTable, "l1");
    }
    if (query == "insert into ReaderAccount (acc_id, phone) values(1, '123') "){
        if (!selectedAccountTable.empty()) {
            ReaderAccountsObjectMother accountsObjectMother;
            ReaderAccount readerAccount(std::shared_ptr<Account>(new Account(selectedAccountTable[selectedAccountTable.size() - 1])), "123");
            selectedReaderAccountTable = accountsObjectMother.getWithAdd(readerAccountTable, readerAccount);
        }
    }
    if (query == "update ReaderAccount set phone = '1234' where acc_id = 5")
    {
        if (!selectedAccountTable.empty()) {
            ReaderAccountsObjectMother accountsObjectMother;
            ReaderAccount readerAccount(std::shared_ptr<Account>(new Account(selectedAccountTable[selectedAccountTable.size() - 1])), "1234");
            readerAccount.getAccount()->setID(5);
            selectedReaderAccountTable = accountsObjectMother.getWithUpd(readerAccountTable, 5, readerAccount);
        }

    }
    if (query == "delete from ReaderAccount where acc_id = 5")
    {
        ReaderAccountsObjectMother accountsObjectMother;
        selectedReaderAccountTable = accountsObjectMother.getWithDel(readerAccountTable, 5);
    }

    if (query == "select LibrarianAccount.id, LibrarianAccount.acc_id, LibrarianAccount.lib_id from Account join LibrarianAccount on LibrarianAccount.acc_id = Account.id join Library on lib_id = Library.id where Account.id = 1")
    {
        LibrarianAccountsObjectMother objectMother;
        selectedLibrarianAccountTable = objectMother.getWithID(librarianAccountTable, 1);
    }
    if (query == "select LibrarianAccount.id, LibrarianAccount.acc_id, LibrarianAccount.lib_id from Account join LibrarianAccount on LibrarianAccount.acc_id = Account.id join Library on lib_id = Library.id where login = 'l1'")
    {
        LibrarianAccountsObjectMother objectMother;
        selectedLibrarianAccountTable = objectMother.getWithLogin(librarianAccountTable, "l1");
    }
    if (query == "insert into LibrarianAccount (acc_id, lib_id) values(1, 4)"){
        if (!selectedAccountTable.empty()) {
            LibrarianAccountsObjectMother objectMother;
            LibrarianAccount librarianAccount(std::shared_ptr<Account>(new Account(selectedAccountTable[selectedAccountTable.size() - 1])), 4);
            selectedLibrarianAccountTable = objectMother.getWithAdd(librarianAccountTable, librarianAccount);
        }
    }
    if (query == "update LibrarianAccount set lib_id = 4 where acc_id = 5")
    {
        if (!selectedAccountTable.empty()) {
            LibrarianAccountsObjectMother objectMother;
            LibrarianAccount librarianAccount(std::shared_ptr<Account>(new Account(selectedAccountTable[selectedAccountTable.size() - 1])), 4);
            librarianAccount.getAccount()->setID(5);
            selectedLibrarianAccountTable = objectMother.getWithUpd(librarianAccountTable, 5, librarianAccount);
        }

    }
    if (query == "delete from LibrarianAccount where acc_id = 5")
    {
        LibrarianAccountsObjectMother objectMother;
        selectedLibrarianAccountTable = objectMother.getWithDel(librarianAccountTable, 5);
    }
}