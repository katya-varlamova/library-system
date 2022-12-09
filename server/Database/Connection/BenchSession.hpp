//
// Created by Екатерина on 04.12.2022.
//

#ifndef SERVERSETTINGS_H_BENCHSESSION_H
#define SERVERSETTINGS_H_BENCHSESSION_H
#include "Session.h"
#include <sys/time.h>
template<>
template<typename INTO_T>
int Session<soci::session>::exec_into(const std::string &query, INTO_T &into)
{
//    clock_t sTime = clock();
    soci::indicator ind = soci::i_ok;
    session << query, soci::into(into, ind);
//    clock_t eTime = clock();
//    double time = (eTime - sTime) / (.001 * CLOCKS_PER_SEC);
//    printf("%lf", time);
    if (ind == soci::i_ok)
        return 0;
    else
        return 1;
}
template<>
template<typename INTO_T>
int Session<soci::session>::exec_into(const std::string &query, std::vector<INTO_T> &into)
{
    clock_t sTime = clock();
    soci::indicator ind = soci::i_ok;
    INTO_T i;
    soci::statement st(session);
    st = (session.prepare <<  query, soci::into(i, ind));

    st.execute();

    while (st.fetch())
        into.push_back(i);
    clock_t eTime = clock();
    double time = (eTime - sTime) / (.001 * CLOCKS_PER_SEC);
    if (query == "select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id left join Account on acc_id = Account.id where Library.name = 'ln1'" ||
        query == "select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id left join Account on acc_id = Account.id where Library.name = 'ln10'" ||
        query == "select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id left join Account on acc_id = Account.id where Library.name = 'ln100'" ||
        query == "select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id left join Account on acc_id = Account.id where Library.name = 'ln500'" ||
        query == "select BookItem.id, book_id, lib_id, acc_id from BookItem join Book on book_id = Book.id join Library on Library.id = lib_id left join Account on acc_id = Account.id where Library.name = 'ln1000'" ||
        query == "select * from Library where Library.name = 'ln1'" ||
        query == "select * from Library where Library.name = 'ln10'" ||
        query == "select * from Library where Library.name = 'ln100'" ||
        query == "select * from Library where Library.name = 'ln500'" ||
        query == "select * from Library where Library.name = 'ln1000'")
        printf("%lf", time);
    if (ind == soci::i_ok)
        return 0;
    else
        return 1;
}
#endif //SERVERSETTINGS_H_BENCHSESSION_H
