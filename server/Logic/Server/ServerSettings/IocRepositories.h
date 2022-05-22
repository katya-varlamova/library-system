//
// Created by Екатерина on 16.05.2022.
//

#ifndef SRC_IOCREPOSITORIES_H
#define SRC_IOCREPOSITORIES_H
#include "../../../Database/Entities/DBAccount/LibrarianAccount/ILibrarianAccountRepository.h"
#include "../../../Database/Entities/DBAccount/AdminAccount/IAdminAccountRepository.h"
#include "../../../Database/Entities/DBAccount/ReaderAccount/IReaderAccountRepository.h"
#include "../../../Database/Entities/DBLibrary/ILibraryRepository.h"
#include "../../../Database/Entities/DBBook/IBookRepository.h"

#include "../../../Database/Entities/DBAccount/LibrarianAccount/LibrarianAccountRepository.h"
#include "../../../Database/Entities/DBAccount/AdminAccount/AdminAccountRepository.h"
#include "../../../Database/Entities/DBAccount/ReaderAccount/ReaderAccountRepository.h"
#include "../../../Database/Entities/DBLibrary/LibraryRepository.h"
#include "../../../Database/Entities/DBBook/BookRepository.h"
class IIocRepository
{
public:
    virtual std::shared_ptr<IAdminAccountRepository> getAdminAccountRepository() = 0;
    virtual std::shared_ptr<ILibraryRepository> getLibraryRepository() = 0;
    virtual std::shared_ptr<ILibrarianAccountRepository> getLibrarianAccountRepository() = 0;
    virtual std::shared_ptr<IReaderAccountRepository> getReaderAccountRepository() = 0;
    virtual std::shared_ptr<IBookRepository> getBookRepository() = 0;
    virtual std::shared_ptr<IAccountRepository> getAccountRepository() = 0;
};
class PGIocRepositories : public IIocRepository
{
public:
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
    std::shared_ptr<ILibraryRepository> getLibraryRepository() override
    {
        return std::shared_ptr<ILibraryRepository>(new LibraryRepository());
    }
    std::shared_ptr<IAccountRepository> getAccountRepository() override
    {
        return std::shared_ptr<IAccountRepository>(new AccountRepository());
    }
};
#endif //SRC_IOCREPOSITORIES_H
