//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_GETFREEBOOKS_H
#define SRC_GETFREEBOOKS_H


#include "BookSpecification.h"
#include <string>
class GetFreeBooks :  public BookSpecification{
public:
    GetFreeBooks(const std::vector<std::shared_ptr<Filter>> &filters)
    {
        this->filters = filters;
    }
    std::vector<DBBook> exec(std::shared_ptr<Session> session) override;

protected:
    std::vector<std::shared_ptr<Filter>> filters;
};

#endif //SRC_GETFREEBOOKS_H
