//
// Created by Екатерина on 28.03.2022.
//

#include "DataAccessFacade.h"
void DataAccessFacade::connectDB()
{
    conn->connect();

}
void DataAccessFacade::execute(Command &command, std::string role)
{
    int pos;
    command.execute( conn->getConnectionByRole(role, pos));
    conn->putConnectionByRole(role, pos);
}
void DataAccessFacade::disconnectDB()
{
    conn->disconnect();
}