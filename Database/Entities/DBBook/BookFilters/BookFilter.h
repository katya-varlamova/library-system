//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_BOOKFILTER_H
#define SRC_BOOKFILTER_H
#include "../../../DataAccessFacade/Commands/Filters/Filter.h"
class BookFilter : public Filter
{
public:
    virtual std::string getEqualClause() = 0;
};
#endif //SRC_BOOKFILTER_H
