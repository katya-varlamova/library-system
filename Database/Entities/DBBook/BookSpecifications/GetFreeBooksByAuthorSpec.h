//
// Created by Екатерина on 10.04.2022.
//

#ifndef SRC_GETFREEBOOKSBYAUTHORSPEC_H
#define SRC_GETFREEBOOKSBYAUTHORSPEC_H

#include "BookSpecification.h"
#include <string>
class GetFreeBooksByAuthorSpec :  public BookSpecification{
public:
    GetFreeBooksByAuthorSpec(const std::string &author)
    {
        this->author = author;
    }
    std::vector<DBBook> exec(soci::session & session) override;

protected:
    std::string author;
};

#endif //SRC_GETFREEBOOKSBYAUTHORSPEC_H
