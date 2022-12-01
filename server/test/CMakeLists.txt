cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 17)
project(test)


add_executable(test
        test.cpp
        TestingSession.cpp
        ObjectMothers/LibrariesObjectMother.cpp
        ObjectMothers/BooksObjectMother.cpp
        ObjectMothers/AccountsObjectMother.cpp
        ObjectMothers/AdminAccountsObjectMother.cpp
        ObjectMothers/ReaderAccountsObjectMother.cpp
        ObjectMothers/LibrarianAccountsObjectMother.cpp
        Mocks/LibraryRepositoryMock.cpp
        Mocks/BookRepositoryMock.cpp
        Mocks/AccountRepositoryMock.cpp
        Mocks/AdminAccountRepositoryMock.cpp
        Mocks/LibrarianAccountRepositoryMock.cpp
        Mocks/ReaderAccountRepositoryMock.cpp
        )

target_compile_definitions(bdtest  PUBLIC TEST_CONFIGURATION=1)
#target_compile_definitions(test  PUBLIC TEST_CONFIGURATION=1)
target_link_libraries(test bl bdtest logger ${Boost_LIBRARIES})
