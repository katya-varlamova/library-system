//
// Created by Екатерина on 29.03.2022.
//

#include "PostgresDataAccessFacade.h"
void PostgresDataAccessFacade::connectDB(const std::vector<std::string> &roles)
{
    conn = std::shared_ptr<Connection>(new Connection());

    conn->registerRoleConnection("admin", 30, "postgresql://host='localhost' port='5433' dbname='postgres' user='postgres' password='rfktdf17'");
    conn->registerRoleConnection("librarian", 30, "postgresql://host='localhost' port='5433' dbname='postgres' user='librarian' password='librarian'");
    conn->registerRoleConnection("reader", 30, "postgresql://host='localhost' port='5433' dbname='postgres' user='reader' password='reader'");
    //conn->registerRoleConnection("librarian", 30, "");
    }

void PostgresDataAccessFacade::createDatabase()
{
    CreateDatabaseCommand cdbc;
    int pos;
    cdbc.execute(conn->getConnectionByRole("admin", pos));
    conn->putConnectionByRole("admin", pos);
}
void PostgresDataAccessFacade::execute(Command &command, std::string role)
{
    int pos;
    command.execute( conn->getConnectionByRole(role, pos));
    conn->putConnectionByRole(role, pos);
}
void PostgresDataAccessFacade::disconnectDB()
{
    conn->disconnect();
}