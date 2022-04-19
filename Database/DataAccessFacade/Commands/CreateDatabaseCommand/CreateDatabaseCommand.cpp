//
// Created by Екатерина on 04.04.2022.
//

#include "CreateDatabaseCommand.h"
void CreateDatabaseCommand::execute(soci::session &session)
{
    session << "create table if not exists Account ("
               "id serial primary key, "
               "login varchar(30) unique, "
               "password varchar(30), "
               "name varchar(30),"
               "role varchar(30) );\n";
    session << "create table if not exists Library ("
               "id serial primary key, "
               "name varchar(30), "
               "address varchar(30) );\n";
    session << "create table if not exists Book ("
               "id serial primary key, "
               "name varchar(40), "
               "author varchar(40) );\n";
    session << "create table if not exists BookItem ("
               "id serial primary key, "
               "book_id int references Book(id), "
               "lib_id int references Library(id), "
               "acc_id int references Account(id) );\n";
}