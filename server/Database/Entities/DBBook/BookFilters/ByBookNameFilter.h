//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_BYBOOKNAMEFILTER_H
#define SRC_BYBOOKNAMEFILTER_H
#include <string>
#include "BookFilter.h"

class ByBookNameFilter : public BookFilter{
public:
    ByBookNameFilter(const std::string &name)
    {
        this->name = name;
    }
    std::string getEqualClause() override
    {
        return "Book.name = '" + name + "'";
    }
private:
    std::string name;
};

#endif //SRC_BYBOOKNAMEFILTER_H
