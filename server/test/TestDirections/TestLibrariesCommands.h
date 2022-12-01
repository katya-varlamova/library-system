//
// Created by Екатерина on 25.11.2022.
//

#ifndef SRC_TESTLIBRARIESCOMMANDS_H
#define SRC_TESTLIBRARIESCOMMANDS_H
#include "DataAccessFacade/Commands/LibraryCommands/DeleteLibrariesCommand.h"
#include "DataAccessFacade/Commands/LibraryCommands/PostLibrariesCommand.h"
#include "DataAccessFacade/Commands/LibraryCommands/UpdateLibraries.h"
#include "DataAccessFacade/Commands/LibraryCommands/GetlibrariesCommand.h"
#include "../test/Mocks/LibraryRepositoryMock.h"

BOOST_AUTO_TEST_CASE(TestGetLibrariesCommand){
    // arrange
    std::shared_ptr<Configuration> configuration = std::shared_ptr<Configuration>(new FileConfiguration("config.json"));
    configuration->read();
    std::vector<std::string> checkSeq = {"query"};
    auto mock = new LibraryRepositoryMock(true);
    std::shared_ptr<ILibraryRepository> repositoryMock = std::shared_ptr<ILibraryRepository> (mock);
    std::vector<std::shared_ptr<Library>> libs;
    std::vector<std::shared_ptr<LibraryFilter>> filters;
    GetlibrariesCommand command = GetlibrariesCommand(repositoryMock,libs, filters);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);
    // assert
    BOOST_CHECK_EQUAL(mock->getSequence() == checkSeq, true);
}

BOOST_AUTO_TEST_CASE(TestPostLibrariesCommandPos){
    // arrange
    std::vector<std::string> checkSeq = {"query", "add"};
    auto mock = new LibraryRepositoryMock(false);
    std::shared_ptr<ILibraryRepository> repositoryMock = std::shared_ptr<ILibraryRepository> (mock);
    std::shared_ptr<Library> lib(new Library("name", "adddress"));
    PostLibrariesCommand command = PostLibrariesCommand(repositoryMock,lib);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);
    // assert
    BOOST_CHECK_EQUAL(mock->getSequence() == checkSeq, true);
}
BOOST_AUTO_TEST_CASE(TestPostLibrariesCommandNeg){
    // arrange
    std::vector<std::string> checkSeq = {"query"};
    auto mock = new LibraryRepositoryMock(true);
    std::shared_ptr<ILibraryRepository> repositoryMock = std::shared_ptr<ILibraryRepository> (mock);
    std::shared_ptr<Library> lib(new Library("name", "adddress"));
    PostLibrariesCommand command = PostLibrariesCommand(repositoryMock,lib);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);
    // assert
    BOOST_CHECK_EQUAL(mock->getSequence() == checkSeq, true);
}
BOOST_AUTO_TEST_CASE(TestUpdateLibrariesCommandPos){
    // arrange
    std::vector<std::string> checkSeq = {"query", "update"};
    auto mock = new LibraryRepositoryMock(true);
    std::shared_ptr<ILibraryRepository> repositoryMock = std::shared_ptr<ILibraryRepository> (mock);
    std::shared_ptr<Library> lib(new Library("name", "adddress"));
    lib->setID(1);
    UpdateLibrariesCommand command = UpdateLibrariesCommand(repositoryMock,lib);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);
    // assert
    BOOST_CHECK_EQUAL(mock->getSequence() == checkSeq, true);
}
BOOST_AUTO_TEST_CASE(TestUpdateLibrariesCommandNeg){
    // arrange
    std::vector<std::string> checkSeq = {"query"};
    auto mock = new LibraryRepositoryMock(false);
    std::shared_ptr<ILibraryRepository> repositoryMock = std::shared_ptr<ILibraryRepository> (mock);
    std::shared_ptr<Library> lib(new Library("name", "adddress"));
    lib->setID(1);
    UpdateLibrariesCommand command = UpdateLibrariesCommand(repositoryMock,lib);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    bool exc = false;

    // act
    try {
        command.execute(session);
    }
    catch (DatabaseException)
    {
        exc = true;
    }

    // assert
    BOOST_CHECK_EQUAL(exc && (mock->getSequence() == checkSeq), true);
}

BOOST_AUTO_TEST_CASE(TestDeleteLibrariesCommandPos){
    // arrange
    std::vector<std::string> checkSeq = {"query", "remove"};
    auto mock = new LibraryRepositoryMock(true);
    std::shared_ptr<ILibraryRepository> repositoryMock = std::shared_ptr<ILibraryRepository> (mock);
    DeleteLibrariesCommand command = DeleteLibrariesCommand(repositoryMock,1);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    // act
    command.execute(session);
    // assert
    BOOST_CHECK_EQUAL(mock->getSequence() == checkSeq, true);
}
BOOST_AUTO_TEST_CASE(TestDeleteLibrariesCommandNeg){
    // arrange
    std::vector<std::string> checkSeq = {"query"};
    auto mock = new LibraryRepositoryMock(false);
    std::shared_ptr<ILibraryRepository> repositoryMock = std::shared_ptr<ILibraryRepository> (mock);
    DeleteLibrariesCommand command = DeleteLibrariesCommand(repositoryMock,1);
    TestingSession ts;
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    bool exc = false;

    // act
    try {
        command.execute(session);
    }
    catch (DatabaseException)
    {
        exc = true;
    }

    // assert
    BOOST_CHECK_EQUAL(exc && (mock->getSequence() == checkSeq), true);
}
#endif //SRC_TESTLIBRARIESCOMMANDS_H
