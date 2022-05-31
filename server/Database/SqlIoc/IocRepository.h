//
// Created by Екатерина on 23.05.2022.
//

#ifndef SRC_IOCREPOSITORY_H
#define SRC_IOCREPOSITORY_H

#include "../Entities/DBAccount/LibrarianAccount/ILibrarianAccountRepository.h"
#include "../Entities/DBAccount/AdminAccount/IAdminAccountRepository.h"
#include "../Entities/DBAccount/ReaderAccount/IReaderAccountRepository.h"
#include "../Entities/DBLibrary/ILibraryRepository.h"
#include "../Entities/DBBook/IBookRepository.h"
#include "../Connection/IConnectionPool.h"
#include "../Entities/DBEBook/IEBookRepository.h"
class IIocRepository
{
public:
    virtual std::shared_ptr<IAdminAccountRepository> getAdminAccountRepository() = 0;
    virtual std::shared_ptr<ILibraryRepository> getLibraryRepository() = 0;
    virtual std::shared_ptr<ILibrarianAccountRepository> getLibrarianAccountRepository() = 0;
    virtual std::shared_ptr<IReaderAccountRepository> getReaderAccountRepository() = 0;
    virtual std::shared_ptr<IBookRepository> getBookRepository() = 0;
    virtual std::shared_ptr<IAccountRepository> getAccountRepository() = 0;
    virtual std::shared_ptr<IConnectionPool> getConnectionPool() = 0;
    virtual std::shared_ptr<AdminRoleConnection> getAdminConnection() = 0;
    virtual std::shared_ptr<ReaderRoleConnection> getReaderConnection() = 0;
    virtual std::shared_ptr<LibrarianRoleConnection> getLibrarianConnection() = 0;
    virtual std::shared_ptr<IEBookRepository> getEBookRepository() = 0;
};


#endif //SRC_IOCREPOSITORY_H
