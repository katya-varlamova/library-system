//
// Created by Екатерина on 23.05.2022.
//

#ifndef SRC_SQLIOC_H
#define SRC_SQLIOC_H


#include "../Entities/DBAccount/LibrarianAccount/LibrarianAccountRepository.h"
#include "../Entities/DBAccount/AdminAccount/AdminAccountRepository.h"
#include "../Entities/DBAccount/ReaderAccount/ReaderAccountRepository.h"
#include "../Entities/DBLibrary/LibraryRepository.h"
#include "../Entities/DBBook/BookRepository.h"
#include "../../Logic/Configuration/Configuration.h"
#include "../Connection/SociConnectionPool.h"
#include "../Entities/DBEBook/EBookRepository.h"
#include "IocRepository.h"
class SqlIocRepositories : public IIocRepository
{
public:
    SqlIocRepositories(std::shared_ptr<Configuration> configuration)
    {
        this->configuration = configuration;
        configuration->read();
    }
    std::shared_ptr<IAdminAccountRepository> getAdminAccountRepository() override
    {
        return std::shared_ptr<IAdminAccountRepository>(new AdminAccountRepository());
    }
    std::shared_ptr<ILibrarianAccountRepository> getLibrarianAccountRepository() override
    {
        return std::shared_ptr<ILibrarianAccountRepository>(new LibrarianAccountRepository());
    }
    std::shared_ptr<IReaderAccountRepository> getReaderAccountRepository() override
    {
        return std::shared_ptr<IReaderAccountRepository>(new ReaderAccountRepository());
    }
    std::shared_ptr<IBookRepository> getBookRepository() override
    {
        return std::shared_ptr<IBookRepository>(new BookRepository());
    }
    std::shared_ptr<IEBookRepository> getEBookRepository() override
    {
        return std::shared_ptr<IEBookRepository>(new EBookRepository());
    }
    std::shared_ptr<ILibraryRepository> getLibraryRepository() override
    {
        return std::shared_ptr<ILibraryRepository>(new LibraryRepository());
    }
    std::shared_ptr<IAccountRepository> getAccountRepository() override
    {
        return std::shared_ptr<IAccountRepository>(new AccountRepository());
    }
    std::shared_ptr<IConnectionPool> getConnectionPool() override
    {
        return std::shared_ptr<IConnectionPool>(new SociConnectionPool({configuration->getLibrarianConnection(),
                                                                        configuration->getAdminConnection(),
                                                                        configuration->getReaderConnection()
                                                                       }));

    }
    std::shared_ptr<AdminRoleConnection> getAdminConnection() override
    {
        return configuration->getAdminConnection();

    }
    std::shared_ptr<LibrarianRoleConnection> getLibrarianConnection() override
    {
        return configuration->getLibrarianConnection();

    }
    std::shared_ptr<ReaderRoleConnection> getReaderConnection() override
    {
        return configuration->getReaderConnection();

    }

private:
    std::shared_ptr<Configuration> configuration;
};

#endif //SRC_SQLIOC_H
