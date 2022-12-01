//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_FILTER_H
#define SRC_FILTER_H
#include <string>
class Filter
{
public:
    virtual std::string getEqualClause() = 0;
};
#endif //SRC_FILTER_H
