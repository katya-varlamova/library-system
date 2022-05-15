create table if not exists Account (
                                       id serial primary key,
                                       login varchar(30) unique,
    password varchar(30),
    name varchar(30),
    role varchar(30) );
create table if not exists Library (
                                       id serial primary key,
                                       name varchar(30),
    address varchar(30) );
create table if not exists LibrarianAccount (
                                                id serial primary key,
                                                acc_id int references Account(id),
    lib_id int references Library(id) );
create table if not exists AdminAccount (
                                            id serial primary key,
                                            acc_id int references Account(id) );
create table if not exists ReaderAccount (
                                             id serial primary key,
                                             acc_id int references Account(id),
    phone varchar(40) );
create table if not exists Book (
                                    id serial primary key,
                                    name varchar(40),
    author varchar(40) );
create table if not exists BookItem (
                                        id serial primary key,
                                        book_id int references Book(id),
    lib_id int references Library(id),
    acc_id int references Account(id) );

create user librarian WITH PASSWORD 'librarian';
grant select on book, bookitem, account, librarianaccount, library to librarian;
grant update on bookitem to librarian;

create user reader WITH PASSWORD 'reader';
grant select on book, bookitem, account, readeraccount, library to reader;

create or replace function take_book(login_user varchar, login_lib varchar, bookname varchar, bookauthor varchar)
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
where name = bookname and author = bookauthor and lib_id = lid and acc_id is null;

update bookitem
set acc_id = aid
where id = biid;
return biid;
end;
$$
LANGUAGE PLPGSQL;


create or replace function return_book(login_user varchar, login_lib varchar, bookname varchar, bookauthor varchar)
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
where name = bookname and author = bookauthor and lib_id = lid and acc_id = aid;

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