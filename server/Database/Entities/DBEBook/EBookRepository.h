//
// Created by Екатерина on 23.05.2022.
//

#ifndef SRC_EBOOKREPOSITORY_H
#define SRC_EBOOKREPOSITORY_H

#include "IEBookRepository.h"
class EBookRepository : public IEBookRepository{
    std::vector<std::shared_ptr<EBook>> query(std::shared_ptr<Session> session, std::shared_ptr<EBookSpecification> specification) override;
    void removeBook(std::shared_ptr<Session> session, int id) override;
    void updateBook(std::shared_ptr<Session> session, std::shared_ptr<EBook> book) override;
    void addBook(std::shared_ptr<Session> session, std::shared_ptr<EBook> book) override;

};


#endif //SRC_EBOOKREPOSITORY_H
