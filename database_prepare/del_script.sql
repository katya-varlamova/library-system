revoke select on book, bookitem, account, librarianaccount, library from librarian;
revoke update on bookitem from librarian;
drop user librarian;

revoke select on book, bookitem, account, readeraccount, library from reader;
drop user reader;


drop trigger if exists bef on Account;
drop function f_delete_acc_trigger;

drop trigger if exists bef_lib on Library;
drop function f_delete_lib_trigger;

drop function take_book;
drop function return_book;

drop table bookitem;
drop table book;
drop table librarianaccount;
drop table adminaccount;
drop table readeraccount;
drop table library;
drop table account;