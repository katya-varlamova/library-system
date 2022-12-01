//
// Created by Екатерина on 27.11.2022.
//

#ifndef SRC_BOOKREPOSITORYMOCK_H
#define SRC_BOOKREPOSITORYMOCK_H

#include "Entities/DBBook/IBookRepository.h"
#include "../ObjectMothers/BooksObjectMother.h"
class BookRepositoryMock : public IBookRepository {
public:
    BookRepositoryMock(bool rv){
        this->rv = rv;
    }
    std::vector<std::shared_ptr<Book>> query(std::shared_ptr<Session<>> session, std::shared_ptr<BookSpecification> specification) override;
    void addBook(std::shared_ptr<Session<>> session, std::shared_ptr<Book> book) override;
    void updateBook(std::shared_ptr<Session<>> session, std::shared_ptr<Book> book) override;
    void removeBook(std::shared_ptr<Session<>> session, int id) override;
    std::vector<std::string> getSequence()
    {
        return call_seq;
    }
private:
    bool rv;
    std::vector<std::string> call_seq;
};



#endif //SRC_BOOKREPOSITORYMOCK_H
