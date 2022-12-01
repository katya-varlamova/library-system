//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_LIBRARYFILTER_H
#define SRC_LIBRARYFILTER_H
#include <string>
#include "../../../DataAccessFacade/Commands/Filters/Filter.h"
class LibraryFilter : public Filter
{
public:
    virtual std::string getEqualClause() = 0;
};
#endif //SRC_LIBRARYFILTER_H
