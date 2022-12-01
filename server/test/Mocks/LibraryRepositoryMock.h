//
// Created by Екатерина on 24.11.2022.
//

#ifndef SRC_LIBRARYREPOSITORYMOCK_H
#define SRC_LIBRARYREPOSITORYMOCK_H
#include "Entities/DBLibrary/ILibraryRepository.h"

class LibraryRepositoryMock : public ILibraryRepository{
public:
    LibraryRepositoryMock(bool rv){
        this->rv = rv;
    }
    std::vector<std::shared_ptr<Library>> query(std::shared_ptr<Session<>> session, std::shared_ptr<LibarySpecification> specification) override;
    int addLibrary(std::shared_ptr<Session<>> session, const std::shared_ptr<Library> &library) override;
    void updateLibrary(std::shared_ptr<Session<>> session, std::shared_ptr<Library> library) override;
    void removeLibrary(std::shared_ptr<Session<>> session, int id) override;
    std::vector<std::string> getSequence()
    {
        return call_seq;
    }
private:
    bool rv;
    std::vector<std::string> call_seq;
};


#endif //SRC_LIBRARYREPOSITORYMOCK_H
