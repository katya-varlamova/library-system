//
// Created by Екатерина on 18.04.2022.
//

#include "DeleteDatabaseCommand.h"
void DeleteDatabaseCommand::execute(std::shared_ptr<Session<>> session)
{
    /*session->exec("revoke select on book, bookitem, account, librarianaccount, library from librarian;\n"
                 "revoke update on bookitem from librarian;\n"
                 "drop user librarian;\n"
                 "revoke select on book, bookitem, account, readeraccount, library from reader;\n"
                 "drop user reader;"*/
//         "drop table book; "
//               "drop table bookitem; "
//               "drop table librarianaccount; "
//               "drop table adminaccount; "
//               "drop table readeraccount; "
//               "drop table library; "
//               "drop table account;");

}