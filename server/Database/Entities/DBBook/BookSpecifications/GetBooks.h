//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_GETBOOKSBYLOGINN_H
#define SRC_GETBOOKSBYLOGINN_H

#include <string>
#include "BookSpecification.h"
class GetBooks :  public BookSpecification{
public:
    GetBooks(const std::vector<std::shared_ptr<Filter>> &filters)
    {
        this->filters = filters;
    }
    std::vector<DBBook> exec(std::shared_ptr<Session> session) override;

protected:
    std::vector<std::shared_ptr<Filter>> filters;
};


#endif //SRC_GETBOOKSBYLOGINN_H
