//
// Created by Екатерина on 04.04.2022.
//

#include "CreateDatabaseCommand.h"
void CreateDatabaseCommand::execute(std::shared_ptr<Session<>> session)
{
//    session->exec("create table if not exists Account ("
//               "id serial primary key, "
//               "login varchar(30) unique, "
//               "password varchar(30), "
//               "name varchar(30),"
//               "role varchar(30) );\n");
//    session->exec("create table if not exists Library ("
//               "id serial primary key, "
//               "name varchar(30), "
//               "address varchar(30) );\n");
//    session->exec("create table if not exists LibrarianAccount ("
//                  "id serial primary key, "
//                  "acc_id int references Account(id),"
//                  "lib_id int references Library(id) );\n");
//    session->exec("create table if not exists AdminAccount ("
//                  "id serial primary key, "
//                  "acc_id int references Account(id) );\n");
//    session->exec("create table if not exists ReaderAccount ("
//                  "id serial primary key, "
//                  "acc_id int references Account(id),"
//                  "phone varchar(40) );\n");
//    session->exec("create table if not exists Book ("
//               "id serial primary key, "
//               "name varchar(40), "
//               "author varchar(40) );\n");
//    session->exec("create table if not exists BookItem ("
//               "id serial primary key, "
//               "book_id int references Book(id), "
//               "lib_id int references Library(id), "
//               "acc_id int references Account(id) );\n");
//    session->exec("create user librarian WITH PASSWORD 'librarian';\n"
//                  "grant select on book, bookitem, account, librarianaccount, library to librarian;\n"
//                  "grant update on bookitem to librarian;\n"
//                  "create user reader WITH PASSWORD 'reader';\n"
//                  "grant select on book, bookitem, account, readeraccount, library to reader;");

}