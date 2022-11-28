cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_STANDARD 17)
project(bd)

add_library(bdtest
        Connection/Session.cpp
        Connection/IConnectionPool.cpp
        Connection/SociConnectionPool.cpp
        Entities/DBEBook/EBookRepository.cpp
        Entities/DBBook/DBBook.cpp
        Entities/DBBook/BookRepository.cpp
        Entities/DBAccount/AccountRepository.cpp
        DataAccessFacade/DataAccessFacade.cpp
        DataAccessFacade/DataAccessFacade.h
        Connection/IConnectionPool.cpp
        DataAccessFacade/Commands/Command.cpp
        DataAccessFacade/Commands/AccountCommands/AuthCommand/AuthCommand.cpp
        Entities/DBLibrary/DBLibrary.cpp
        Entities/DBLibrary/LibraryRepository.cpp
        Entities/DBBook/BookSpecifications/BookSpecification.cpp
        DataAccessFacade/Commands/AccountCommands/RegisterCommand/RegisterAdminCommand.cpp
        DataAccessFacade/Commands/unused/CreateDatabaseCommand/CreateDatabaseCommand.cpp
        Entities/DBBook/BookConverter.cpp
        Entities/DBLibrary/LibraryConverter.cpp
        DataAccessFacade/Commands/BookCommands/AddBooksCommand.cpp
        Entities/DBBook/BookSpecifications/TakeBookSpecification.cpp
        DatabseException.cpp
        DataAccessFacade/Commands/unused/DeleteDatabaseCommand/DeleteDatabaseCommand.cpp
        Entities/DBBook/BookSpecifications/GetFreeBooks.cpp
        Entities/DBLibrary/LibrarySpecifications/GetLibrary.cpp
        Entities/DBAccount/AccountSpecifications/GetAccount.cpp
        DataAccessFacade/Commands/BookCommands/GetFreeBooksCommand.cpp
        DataAccessFacade/Commands/BookCommands/GetBooksByLoginCommand.cpp
        Entities/DBBook/BookSpecifications/GetBooks.cpp
        Entities/DBAccount/AdminAccount/AdminAccountRepository.cpp
        Entities/DBAccount/LibrarianAccount/LibrarianAccountRepository.cpp
        Entities/DBAccount/ReaderAccount/ReaderAccountRepository.cpp
        Entities/DBAccount/AdminAccount/AdminAccountSpecifications/GetAdminAccount.cpp
        Entities/DBAccount/LibrarianAccount/LibrarianAccountSpecifications/GetLibrarianAccount.cpp
        Entities/DBAccount/ReaderAccount/ReaderAccountSpecifications/GetReaderAccount.cpp
        DataAccessFacade/Commands/AccountCommands/RegisterCommand/RegisterReaderCommand.cpp
        DataAccessFacade/Commands/AccountCommands/RegisterCommand/RegisterLibrarianCommand.cpp
        Entities/DBBook/BookSpecifications/ReturnBookSpecification.cpp
        DataAccessFacade/Commands/BookCommands/TakeBookCommand/TakeBookCommand.cpp
        DataAccessFacade/Commands/BookCommands/ReturnBookCommand/ReturnBookCommand.cpp
        DataAccessFacade/Commands/LibraryCommands/GetlibrariesCommand.cpp
        DataAccessFacade/Commands/LibraryCommands/UpdateLibraries.cpp
        DataAccessFacade/Commands/LibraryCommands/PostLibrariesCommand.cpp
        DataAccessFacade/Commands/BookCommands/UpdateBookCommand.cpp
        DataAccessFacade/Commands/BookCommands/DeleteBooksCommand.cpp
        Entities/DBBook/BookSpecifications/GetBooks.cpp
        DataAccessFacade/Commands/LibraryCommands/DeleteLibrariesCommand.cpp
        Entities/DBEBook/EBookSpecifications/GetEBooksSpecification.cpp
        Entities/DBBook/BookFilters/ByBookIDFilter.h
        )

add_library(bdrun
        Connection/Session.cpp
        Connection/IConnectionPool.cpp
        Connection/SociConnectionPool.cpp
        Entities/DBEBook/EBookRepository.cpp
        Entities/DBBook/DBBook.cpp
        Entities/DBBook/BookRepository.cpp
        Entities/DBAccount/AccountRepository.cpp
        DataAccessFacade/DataAccessFacade.cpp
        DataAccessFacade/DataAccessFacade.h
        Connection/IConnectionPool.cpp
        DataAccessFacade/Commands/Command.cpp
        DataAccessFacade/Commands/AccountCommands/AuthCommand/AuthCommand.cpp
        Entities/DBLibrary/DBLibrary.cpp
        Entities/DBLibrary/LibraryRepository.cpp
        Entities/DBBook/BookSpecifications/BookSpecification.cpp
        DataAccessFacade/Commands/AccountCommands/RegisterCommand/RegisterAdminCommand.cpp
        DataAccessFacade/Commands/unused/CreateDatabaseCommand/CreateDatabaseCommand.cpp
        Entities/DBBook/BookConverter.cpp
        Entities/DBLibrary/LibraryConverter.cpp
        DataAccessFacade/Commands/BookCommands/AddBooksCommand.cpp
        Entities/DBBook/BookSpecifications/TakeBookSpecification.cpp
        DatabseException.cpp
        DataAccessFacade/Commands/unused/DeleteDatabaseCommand/DeleteDatabaseCommand.cpp
        Entities/DBBook/BookSpecifications/GetFreeBooks.cpp
        Entities/DBLibrary/LibrarySpecifications/GetLibrary.cpp
        Entities/DBAccount/AccountSpecifications/GetAccount.cpp
        DataAccessFacade/Commands/BookCommands/GetFreeBooksCommand.cpp
        DataAccessFacade/Commands/BookCommands/GetBooksByLoginCommand.cpp
        Entities/DBBook/BookSpecifications/GetBooks.cpp
        Entities/DBAccount/AdminAccount/AdminAccountRepository.cpp
        Entities/DBAccount/LibrarianAccount/LibrarianAccountRepository.cpp
        Entities/DBAccount/ReaderAccount/ReaderAccountRepository.cpp
        Entities/DBAccount/AdminAccount/AdminAccountSpecifications/GetAdminAccount.cpp
        Entities/DBAccount/LibrarianAccount/LibrarianAccountSpecifications/GetLibrarianAccount.cpp
        Entities/DBAccount/ReaderAccount/ReaderAccountSpecifications/GetReaderAccount.cpp
        DataAccessFacade/Commands/AccountCommands/RegisterCommand/RegisterReaderCommand.cpp
        DataAccessFacade/Commands/AccountCommands/RegisterCommand/RegisterLibrarianCommand.cpp
        Entities/DBBook/BookSpecifications/ReturnBookSpecification.cpp
        DataAccessFacade/Commands/BookCommands/TakeBookCommand/TakeBookCommand.cpp
        DataAccessFacade/Commands/BookCommands/ReturnBookCommand/ReturnBookCommand.cpp
        DataAccessFacade/Commands/LibraryCommands/GetlibrariesCommand.cpp
        DataAccessFacade/Commands/LibraryCommands/UpdateLibraries.cpp
        DataAccessFacade/Commands/LibraryCommands/PostLibrariesCommand.cpp
        DataAccessFacade/Commands/BookCommands/UpdateBookCommand.cpp
        DataAccessFacade/Commands/BookCommands/DeleteBooksCommand.cpp
        Entities/DBBook/BookSpecifications/GetBooks.cpp
        DataAccessFacade/Commands/LibraryCommands/DeleteLibrariesCommand.cpp
        Entities/DBEBook/EBookSpecifications/GetEBooksSpecification.cpp
        Entities/DBBook/BookFilters/ByBookIDFilter.h
        )
target_include_directories(bdrun PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )
target_compile_definitions(bdrun  PUBLIC TEST_CONFIGURATION=0)
target_link_libraries(bdrun SOCI::soci_core PostgreSQL::PostgreSQL)

target_include_directories(bdtest PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )
target_compile_definitions(bdtest  PUBLIC TEST_CONFIGURATION=1)
target_link_libraries(bdtest SOCI::soci_core PostgreSQL::PostgreSQL)