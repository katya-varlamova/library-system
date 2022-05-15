//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_BYADDRESSFILTER_H
#define SRC_BYADDRESSFILTER_H
#include "LibraryFilter.h"

class ByAddressFilter : public LibraryFilter{
public:
    ByAddressFilter(const std::string &address)
    {
        this->address = address;
    }
    std::string getEqualClause() override
    {
        return "address = '" + address + "'";
    }
private:
    std::string address;
};
#endif //SRC_BYADDRESSFILTER_H
