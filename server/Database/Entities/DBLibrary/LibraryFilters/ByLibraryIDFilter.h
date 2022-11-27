//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_BYLIBRARYIDFILTER_H
#define SRC_BYLIBRARYIDFILTER_H
#include "LibraryFilter.h"
class ByLibraryIDFilter : public LibraryFilter{
public:
    ByLibraryIDFilter(int id)
    {
        this->id = id;
    }
    std::string getEqualClause() override
    {
        return "Library.id = " + std::to_string(id);
    }
private:
    int id;
};
#endif //SRC_BYLIBRARYIDFILTER_H
