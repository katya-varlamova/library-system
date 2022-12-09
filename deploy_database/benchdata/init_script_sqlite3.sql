drop table Account ;
create table if not exists Account (
                                       id integer primary key autoincrement,
                                       login varchar(30) unique,
    password varchar(30),
    name varchar(30),
    role varchar(30) );
create table if not exists Accounttemp (
                                       login varchar(30) unique,
    password varchar(30),
    name varchar(30),
    role varchar(30) );
.separator ";"
.import "data/account.csv" Accounttemp
INSERT INTO Account(login, password, name, role) SELECT * FROM Accounttemp;
drop table Accounttemp ;

drop table Library;
create table if not exists Library (
                                       id integer primary key autoincrement,
                                       name varchar(30),
    address varchar(30) );
create table if not exists Librarytemp (
                                       name varchar(30),
    address varchar(30) );
.separator ";"
.import "data/library.csv" Librarytemp
INSERT INTO Library(name, address) SELECT * FROM Librarytemp;
drop table Librarytemp;

drop table LibrarianAccount;
create table if not exists LibrarianAccount (
                                                id integer primary key autoincrement,
                                                acc_id int references Account(id),
    lib_id int references Library(id) );
create table if not exists LibrarianAccounttemp (
                                                acc_id int references Account(id),
    lib_id int references Library(id) );
.separator ";"
.import "data/librarianaccount.csv" LibrarianAccounttemp
INSERT INTO LibrarianAccount(acc_id, lib_id) SELECT * FROM LibrarianAccounttemp;
drop table LibrarianAccounttemp;

drop table AdminAccount;
create table if not exists AdminAccount (
                                            id integer primary key autoincrement,
                                            acc_id int references Account(id) );
create table if not exists AdminAccounttemp (
                                            acc_id int references Account(id) );
.separator ";"
.import "data/adminaccount.csv" AdminAccounttemp
INSERT INTO AdminAccount(acc_id) SELECT * FROM AdminAccounttemp;
drop table AdminAccounttemp;

drop table ReaderAccount;
create table if not exists ReaderAccount (
                                             id integer primary key autoincrement,
                                             acc_id int references Account(id),
    phone varchar(40) );
create table if not exists ReaderAccount (
                                             acc_id int references Account(id),
    phone varchar(40) );
.separator ";"
.import "data/readeraccount.csv" ReaderAccounttemp
INSERT INTO ReaderAccount(phone, acc_id) SELECT * FROM ReaderAccounttemp;
drop table ReaderAccounttemp;

drop table Book;
create table if not exists Book (
                                    id integer primary key autoincrement,
                                    name varchar(40),
    author varchar(40) );
create table if not exists Booktemp (
                                    name varchar(40),
    author varchar(40) );
.separator ";"
.import "data/book.csv" Booktemp
INSERT INTO Book(name, author) SELECT * FROM Booktemp;
drop table Booktemp;

drop table BookItem;
create table if not exists BookItem (
                                        id integer primary key autoincrement,
                                        book_id int references Book(id),
    lib_id int references Library(id),
    acc_id int references Account(id) );
create table if not exists BookItemtemp (
                                        book_id int references Book(id),
    lib_id int references Library(id),
    acc_id int references Account(id) );
.separator ";"
.import "data/bookitem.csv" BookItemtemp
INSERT INTO BookItem(book_id, lib_id, acc_id) SELECT * FROM BookItemtemp;
drop table BookItemtemp;