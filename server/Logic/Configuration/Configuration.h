//
// Created by Екатерина on 22.05.2022.
//

#ifndef SRC_CONFIGURATION_H
#define SRC_CONFIGURATION_H
#include <string>
#include "../../Database/Connection/RoleConnection.h"

class Configuration {
public:
    virtual void read() = 0;
    std::shared_ptr<AdminRoleConnection> getAdminConnection()
    {
        return ac;
    }
    std::shared_ptr<ReaderRoleConnection> getReaderConnection()
    {
        return rc;
    }
    virtual std::shared_ptr<LibrarianRoleConnection> getLibrarianConnection()
    {
        return lc;
    }
protected:
    std::shared_ptr<AdminRoleConnection> ac;
    std::shared_ptr<ReaderRoleConnection> rc;
    std::shared_ptr<LibrarianRoleConnection> lc;

};


#endif //SRC_CONFIGURATION_H
