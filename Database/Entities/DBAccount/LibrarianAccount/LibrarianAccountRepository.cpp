//
// Created by Екатерина on 10.05.2022.
//

#include "LibrarianAccountRepository.h"
#include "../../../DatabseException.h"

std::vector<std::shared_ptr<LibrarianAccount>> LibrarianAccountRepository::query(std::shared_ptr<Session> session, std::shared_ptr<LibrarianAccountSpecification> specification)
{
    std::vector<DBLibrarianAccount> dbacc = specification->exec(session);
    std::vector<std::shared_ptr<LibrarianAccount>> vec;
    LibrarianAccountConverter converter;
    AccountRepository ar;
    LibraryRepository lr;
    for (auto &i : dbacc) {
        std::vector<std::shared_ptr<Account>> accs = ar.query(session, std::shared_ptr<AccountSpecification>(new GetAccount({std::shared_ptr<AccountFilter>(new ByAccountIDFilter(i.acc_id))})));
        std::vector<std::shared_ptr<Library>> libs = lr.query(session, std::shared_ptr<LibarySpecification>(new GetLibrary({std::shared_ptr<LibraryFilter>(new ByLibraryIDFilter(i.lib_id))})));
        if (accs.size() == 1 && libs.size() == 1)
            vec.push_back(converter.convert(accs[0], libs[0]));
        else
            throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                    "library or account don't exist!");
    }
    return vec;
}
void LibrarianAccountRepository::addAccount(std::shared_ptr<Session> session, std::shared_ptr<LibrarianAccount> account)
{
    AccountRepository ar;
    int acc_id = ar.addAccount(session, account->getAccount());

    std::vector<std::shared_ptr<LibraryFilter>> filters = {
            std::shared_ptr<LibraryFilter>(new ByAddressFilter(account->getLibrary()->getAddress())),
            std::shared_ptr<LibraryFilter>(new ByLibraryNameFilter(account->getLibrary()->getName()))
    };
    LibraryRepository lr;
    std::vector<std::shared_ptr<Library>> libs = lr.query(session, std::shared_ptr<LibarySpecification>(new GetLibrary(filters)));
    int lib_id;
    if (libs.size() == 1)
        lib_id = libs[0]->getID();
    else
        throw DatabaseException(__FILE__, __LINE__, __TIME__,
                                "library doesn't exist!");

    LibrarianAccountConverter lac;
    DBLibrarianAccount dblacc = lac.convert(lib_id, acc_id);

    session->exec_using("insert into public.LibrarianAccount "
                        "values(default, :acc_id, :lib_id)", dblacc);

}
void LibrarianAccountRepository::updateAccount(std::shared_ptr<Session> session,
                                               std::shared_ptr<LibrarianAccount> account)
{
    AccountRepository ar;
    ar.updateAccount(session, account->getAccount());
    session->exec_using("update LibrarianAccount set lib_id = :lib_id "
                        "where acc_id = " + std::to_string(account->getAccount()->getID()),
                        account->getLibrary()->getID());
}
void LibrarianAccountRepository::removeAccount(std::shared_ptr<Session> session, int id){
    std::string q = "delete from LibrarianAccount "
                    "where acc_id = " + std::to_string(id);
    session->exec(q);
    AccountRepository repository;
    repository.removeAccount(session, id);
}