//
// Created by Екатерина on 09.04.2022.
//

#ifndef SRC_GETFREEBOOKSBYNAMESPEC_H
#define SRC_GETFREEBOOKSBYNAMESPEC_H

#include "BookSpecification.h"
#include <string>
class GetFreeBooksByNameSpec :  public BookSpecification{
public:
    GetFreeBooksByNameSpec(std::string &name)
    {
        this->name = name;
    }
    std::vector<DBBook> exec(soci::session & session) override;

protected:
    std::string name;
};


#endif //SRC_GETFREEBOOKSBYNAMESPEC_H
