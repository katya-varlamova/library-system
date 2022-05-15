//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_BYAUTHORFILTER_H
#define SRC_BYAUTHORFILTER_H
#include <string>
#include "BookFilter.h"

class ByAuthorFilter : public BookFilter{
public:
    ByAuthorFilter(const std::string &author)
    {
        this->author = author;
    }
    std::string getEqualClause() override
    {
        return "author = '" + author + "'";
    }
private:
    std::string author;
};

#endif //SRC_BYAUTHORFILTER_H
