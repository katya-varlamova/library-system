//
// Created by Екатерина on 24.10.2022.
//

#ifndef SERVERCONTROLLER_H_BYBOOKIDFILTER_H
#define SERVERCONTROLLER_H_BYBOOKIDFILTER_H

#include "BookFilter.h"

class ByBookIDFilter : public BookFilter{
public:
    ByBookIDFilter(int id)
    {
        this->id = id;
    }
    std::string getEqualClause() override
    {
        return "Bookitem.id = " + std::to_string(id);
    }
private:
    int id;
};


#endif //SERVERCONTROLLER_H_BYBOOKIDFILTER_H
