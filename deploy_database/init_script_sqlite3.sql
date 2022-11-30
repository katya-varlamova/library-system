create table if not exists Account (
                                       id integer primary key autoincrement,
                                       login varchar(30) unique,
    password varchar(30),
    name varchar(30),
    role varchar(30) );
create table if not exists Library (
                                       id integer primary key autoincrement,
                                       name varchar(30),
    address varchar(30) );
create table if not exists LibrarianAccount (
                                                id integer primary key autoincrement,
                                                acc_id int references Account(id),
    lib_id int references Library(id) );
create table if not exists AdminAccount (
                                            id integer primary key autoincrement,
                                            acc_id int references Account(id) );
create table if not exists ReaderAccount (
                                             id integer primary key autoincrement,
                                             acc_id int references Account(id),
    phone varchar(40) );
create table if not exists Book (
                                    id integer primary key autoincrement,
                                    name varchar(40),
    author varchar(40) );
create table if not exists BookItem (
                                        id integer primary key autoincrement,
                                        book_id int references Book(id),
    lib_id int references Library(id),
    acc_id int references Account(id) );
create table if not exists EBook (
                                     id integer primary key autoincrement,
                                     book_id int references Book(id),
    link varchar(40));