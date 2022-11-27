//
// Created by Екатерина on 24.11.2022.
//

#include "LibraryRepositoryMock.h"
std::vector<std::shared_ptr<Library>> LibraryRepositoryMock::query(std::shared_ptr<Session<>> session,
                                                                   std::shared_ptr<LibarySpecification> specification){
    call_seq.push_back("query");
    if (!rv)
        return std::vector<std::shared_ptr<Library>>();
    LibrariesObjectMother objectMother;
    std::vector<Library> libs = objectMother.getDefault();
    std::vector<std::shared_ptr<Library>> plibs;
    for (auto l : libs)
    {
        std::shared_ptr<Library> lib(new Library(l));
        plibs.push_back(lib);
    }
    return plibs;
}
int LibraryRepositoryMock::addLibrary(std::shared_ptr<Session<>> session, const std::shared_ptr<Library> &library)
{
    call_seq.push_back("add");
    return rv;
}
void LibraryRepositoryMock::updateLibrary(std::shared_ptr<Session<>> session, std::shared_ptr<Library> library)
{
    call_seq.push_back("update");
}
void LibraryRepositoryMock::removeLibrary(std::shared_ptr<Session<>> session, int id)
{
    call_seq.push_back("remove");
}