//
// Created by Екатерина on 08.05.2022.
//

#ifndef SRC_ACCOUNTFILTER_H
#define SRC_ACCOUNTFILTER_H
#include "../../../DataAccessFacade/Commands/Filters/Filter.h"
class AccountFilter : public Filter
{
public:
    virtual std::string getEqualClause() = 0;
};
#endif //SRC_ACCOUNTFILTER_H
