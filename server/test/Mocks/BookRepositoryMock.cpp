//
// Created by Екатерина on 27.11.2022.
//

#include "BookRepositoryMock.h"


std::vector<std::shared_ptr<Book>> BookRepositoryMock::query(std::shared_ptr<Session<>> session,
                                                                   std::shared_ptr<BookSpecification> specification){
    call_seq.push_back("query");
    if (!rv)
        return std::vector<std::shared_ptr<Book>>();
    BooksObjectMother objectMother;
    std::vector<Book> books = objectMother.getDefault();
    std::vector<std::shared_ptr<Book>> pbooks;
    for (auto l : books)
    {
        std::shared_ptr<Book> b(new Book(l));
        pbooks.push_back(b);
    }
    return pbooks;
}
void BookRepositoryMock::addBook(std::shared_ptr<Session<>> session, std::shared_ptr<Book> book)
{
    call_seq.push_back("add");
}
void BookRepositoryMock::updateBook(std::shared_ptr<Session<>> session, std::shared_ptr<Book> Book)
{
    call_seq.push_back("update");
}
void BookRepositoryMock::removeBook(std::shared_ptr<Session<>> session, int id)
{
    call_seq.push_back("remove");
}