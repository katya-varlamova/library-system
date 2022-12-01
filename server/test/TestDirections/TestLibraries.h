//
// Created by Екатерина on 20.11.2022.
//

#ifndef SRC_TESTLIBRARIES_H
#define SRC_TESTLIBRARIES_H
#include <boost/test/unit_test.hpp>
#include <Entities/DBLibrary/LibraryFilters/ByLibraryIDFilter.h>
#include "../Database/Connection/Session.h"
#include "../Database/Entities/DBLibrary/LibraryRepository.h"
#include "../Stubs/LibrarySpecificationStub.h"

BOOST_AUTO_TEST_CASE(TestGetLibrarySpecificationByName){
    // arrange
    LibrariesObjectMother objectMother;
    std::vector<Library> initial = objectMother.getDefault();
    std::vector<Library> forCheck = objectMother.getWithName(initial, "lib1");

    TestingSession ts;
    ts.initLibraryTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetLibrary> getLibrarySpec  = std::shared_ptr<GetLibrary>(new GetLibrary(std::vector<std::shared_ptr<LibraryFilter>> ({std::shared_ptr<LibraryFilter>(new ByLibraryNameFilter("lib1"))})));
    std::shared_ptr<LibarySpecification> lspec = std::shared_ptr<LibarySpecification>(getLibrarySpec);

    // act
    lspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedLibraryTable() == forCheck, true);
}
BOOST_AUTO_TEST_CASE(TestGetLibrarySpecificationByAddress){
    // arrange
    LibrariesObjectMother objectMother;
    std::vector<Library> initial = objectMother.getDefault();
    std::vector<Library> forCheck = objectMother.getWithAddress(initial, "addr2");

    TestingSession ts;
    ts.initLibraryTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetLibrary> getLibrarySpec  = std::shared_ptr<GetLibrary>(new GetLibrary(std::vector<std::shared_ptr<LibraryFilter>> ({std::shared_ptr<LibraryFilter>(new ByAddressFilter("addr2"))})));
    std::shared_ptr<LibarySpecification> lspec = std::shared_ptr<LibarySpecification>(getLibrarySpec);

    // act
    lspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedLibraryTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestGetLibrarySpecificationByID){
    // arrange
    LibrariesObjectMother objectMother;
    std::vector<Library> initial = objectMother.getDefault();
    std::vector<Library> forCheck = objectMother.getWithID(initial, 1);

    TestingSession ts;
    ts.initLibraryTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetLibrary> getLibrarySpec  = std::shared_ptr<GetLibrary>(new GetLibrary(std::vector<std::shared_ptr<LibraryFilter>> ({std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(1))})));
    std::shared_ptr<LibarySpecification> lspec = std::shared_ptr<LibarySpecification>(getLibrarySpec);

    // act
    lspec->exec(session);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedLibraryTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestGetLibraryRepositoryQueryClassic){
    // arrange
    LibrariesObjectMother objectMother;
    std::vector<Library> initial = objectMother.getDefault();
    std::vector<Library> forCheck = objectMother.getWithID(initial, 1);

    TestingSession ts;
    ts.initLibraryTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));
    std::shared_ptr<GetLibrary> getLibrarySpec  = std::shared_ptr<GetLibrary>(new GetLibrary(std::vector<std::shared_ptr<LibraryFilter>> ({std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(1))})));
    std::shared_ptr<LibarySpecification> lspec = std::shared_ptr<LibarySpecification>(getLibrarySpec);
    LibraryRepository repository;

    // act
    repository.query(session, lspec);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedLibraryTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestGetLibraryRepositoryQueryLondon) {
    // arrange
    LibrariesObjectMother objectMother;
    std::vector<Library> initial = objectMother.getDefault();
    std::vector<Library> forCheck = objectMother.getWithID(initial, 1);

    TestingSession ts;
    ts.initLibraryTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));

    std::shared_ptr<LibarySpecification> lspec = std::shared_ptr<LibarySpecification>(new LibrarySpecificationStub());
    LibraryRepository repository;

    // act
    repository.query(session, lspec);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedLibraryTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestGetLibraryRepositoryAdd) {
    // arrange
    LibrariesObjectMother objectMother;
    std::vector<Library> initial = objectMother.getDefault();
    std::vector<Library> forCheck = objectMother.getWithAdd(initial, "name", "address");

    TestingSession ts;
    ts.initLibraryTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));

    LibraryRepository repository;

    // act
    repository.addLibrary(session, std::shared_ptr<Library>(new Library("name", "address")));

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedLibraryTable() == forCheck, true);
}

BOOST_AUTO_TEST_CASE(TestGetLibraryRepositoryUpd) {
    // arrange
    LibrariesObjectMother objectMother;
    std::vector<Library> initial = objectMother.getDefault();
    std::vector<Library> forCheck = objectMother.getWithUpd(initial, 1, Library("uplib1", "upaddr1"));

    TestingSession ts;
    ts.initLibraryTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));

    std::shared_ptr<Library> l  = std::shared_ptr<Library>(new Library("uplib1", "upaddr1"));
    l->setID(1);

    LibraryRepository repository;

    // act
    repository.updateLibrary(session, std::shared_ptr<Library>(l));

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedLibraryTable() == forCheck, true);
}


BOOST_AUTO_TEST_CASE(TestGetLibraryRepositoryDel) {
    // arrange
    LibrariesObjectMother objectMother;
    std::vector<Library> initial = objectMother.getDefault();
    std::vector<Library> forCheck = objectMother.getWithDel(initial, 1);

    TestingSession ts;
    ts.initLibraryTable(initial);
    std::shared_ptr<Session<>> session = std::shared_ptr<Session<>>(new Session<>(ts));

    LibraryRepository repository;

    // act
    repository.removeLibrary(session, 1);

    // assert
    BOOST_CHECK_EQUAL(ts.getSelectedLibraryTable() == forCheck, true);
}
#endif //SRC_TESTLIBRARIES_H
