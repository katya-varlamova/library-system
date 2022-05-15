//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_GETLIBRARY_H
#define SRC_GETLIBRARY_H


#include "LibarySpecification.h"
#include "../LibraryFilters/LibraryFilter.h"

class GetLibrary : public LibarySpecification{
public:
    GetLibrary(const std::vector<std::shared_ptr<LibraryFilter>> &filters)
    {
        this->filters = filters;
    }
    std::vector<DBLibrary> exec(std::shared_ptr<Session> session) override;

protected:
    std::vector<std::shared_ptr<LibraryFilter>> filters;
};



#endif //SRC_GETLIBRARY_H
