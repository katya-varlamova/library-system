//
// Created by Екатерина on 17.04.2022.
//

#ifndef SRC_TAKEBOOKSPECIFICATION_H
#define SRC_TAKEBOOKSPECIFICATION_H

#include "BookSpecification.h"
class TakeBookSpecification : public BookSpecification {
public:
    TakeBookSpecification(int acc_id, int book_id)
    {
        this->acc_id = acc_id;
    }
    std::vector<DBBook> exec(soci::session &session) override;
private:
    int acc_id;
    int book_id;
};


#endif //SRC_TAKEBOOKSPECIFICATION_H
