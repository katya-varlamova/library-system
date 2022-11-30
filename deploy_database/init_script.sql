DROP database IF EXISTS test;
create database test;
\c test
create table if not exists Account (
                                       id serial primary key,
                                       login varchar(200) unique,
    password varchar(200),
    name varchar(200),
    role varchar(200) );
\copy Account(login, password, name, role) from '/__w/library-system/library-system/deploy_database/data/account.csv' delimiter ';' csv;
create table if not exists Library (
                                       id serial primary key,
                                       name varchar(200),
    address varchar(200) );
\copy Library(name, address) from '/__w/library-system/library-system/deploy_database/data/library.csv' delimiter ';' csv;
create table if not exists LibrarianAccount (
                                                id serial primary key,
                                                acc_id int references Account(id),
    lib_id int references Library(id) );
\copy LibrarianAccount(acc_id, lib_id) from '/__w/library-system/library-system/deploy_database/data/librarianaccount.csv' delimiter ';' csv;
create table if not exists AdminAccount (
                                            id serial primary key,
                                            acc_id int references Account(id) );
\copy AdminAccount(acc_id) from '/__w/library-system/library-system/deploy_database/data/adminaccount.csv' delimiter ';' csv;
create table if not exists ReaderAccount (
                                             id serial primary key,
                                             acc_id int references Account(id),
    phone varchar(200) );
\copy ReaderAccount(acc_id, phone) from '/__w/library-system/library-system/deploy_database/data/readeraccount.csv' delimiter ';' csv;
create table if not exists Book (
                                    id serial primary key,
                                    name varchar(200),
    author varchar(200) );
\copy Book(name, author) from '/__w/library-system/library-system/deploy_database/data/book.csv' delimiter ';' csv;
create table if not exists BookItem (
                                        id serial primary key,
                                        book_id int references Book(id),
    lib_id int references Library(id),
    acc_id int references Account(id) );
\copy BookItem(book_id, lib_id, acc_id) from '/__w/library-system/library-system/deploy_database/data/bookitem.csv' delimiter ';' csv;
create table if not exists EBook (
                                        id serial primary key,
                                        book_id int references Book(id),
    link varchar(200));
create user librarian WITH PASSWORD 'librarian';
grant select on book, bookitem, account, librarianaccount, library to librarian;
grant update on bookitem to librarian;

create user reader WITH PASSWORD 'reader';
grant select on book, bookitem, account, readeraccount, library to reader;

create or replace function take_book(login_user varchar, login_lib varchar, bid_p int)
returns int
as $$
declare
lid int;
	aid int;
	biid int;
begin
select into lid max(lib_id)
from LibrarianAccount join Library on Library.id = lib_id join Account on acc_id = Account.id
where login_lib = login;

select into aid max(id)
from Account
where login = login_user;

select into biid min(bookitem.id)
from bookitem join book on book_id = Book.id
where bookitem.id = bid_p and lib_id = lid and acc_id is null;

update bookitem
set acc_id = aid
where id = biid;
return biid;
end;
$$
LANGUAGE PLPGSQL;


create or replace function return_book(login_user varchar, login_lib varchar, bid_p int)
returns int
as $$
declare
lid int;
	aid int;
	biid int;
begin
select into lid max(lib_id)
from LibrarianAccount join Library on Library.id = lib_id join Account on acc_id = Account.id
where login_lib = login;

select into aid max(id)
from Account
where login = login_user;

select into biid min(bookitem.id)
from bookitem join book on book_id = Book.id
where bookitem.id = bid_p and lib_id = lid and acc_id = aid;

update bookitem
set acc_id = null
where id = biid;
return biid;
end;
$$
LANGUAGE PLPGSQL;

create or replace function f_delete_acc_trigger()
returns trigger
as
$$
begin
update BookItem
set acc_id = null
where acc_id = old.id;

return old;
end
$$  language plpgsql;


create or replace trigger bef before delete on Account
    for each row
    execute procedure f_delete_acc_trigger();

create or replace function f_delete_lib_trigger()
returns trigger
as
$$
declare
ids integer[];
begin
delete from BookItem
where lib_id = old.id;

select into ids array_agg(LibrarianAccount.acc_id)
from LibrarianAccount join Library on Library.id = lib_id
where lib_id = old.id;

delete from LibrarianAccount
where lib_id = old.id;

delete from Account
where id = any(ids);

return old;
end
$$  language plpgsql;


create or replace trigger bef_lib before delete on Library
    for each row
    execute procedure f_delete_lib_trigger();