//
// Created by Екатерина on 10.05.2022.
//

#include "ReaderAccountRepository.h"
#include "../../../../Logger/Logger.h"

std::vector<std::shared_ptr<ReaderAccount>> ReaderAccountRepository::query(std::shared_ptr<Session<>> session, std::shared_ptr<ReaderAccountSpecification> specification)
{
    std::vector<DBReaderAccount> dbacc = specification->exec(session);
    std::vector<std::shared_ptr<ReaderAccount>> vec;
    ReaderAccountConverter converter;
    AccountRepository ar;
    for (auto &i : dbacc) {
        std::vector<std::shared_ptr<Account>> accs = ar.query(session, std::shared_ptr<AccountSpecification>(new GetAccount({std::shared_ptr<AccountFilter>(new ByAccountIDFilter(i.acc_id))})));
        if (accs.size() == 1)
            vec.push_back(converter.convert(accs[0], i));
        else {
            // Logger::getInstance()->log(1, __FILE__, __LINE__, __TIME__,"account doesn't exist!");
            // throw DatabaseException(__FILE__, __LINE__, __TIME__, "library or account don't exist!");
        }
    }
    return vec;
}
void ReaderAccountRepository::addAccount(std::shared_ptr<Session<>> session, std::shared_ptr<ReaderAccount> account)
{
    AccountRepository ar;
    int acc_id = ar.addAccount(session, account->getAccount());

    ReaderAccountConverter rac;
    DBReaderAccount dbracc = rac.convert(account, acc_id);

    session->exec("insert into ReaderAccount (acc_id, phone) "
                  "values(" + std::to_string(dbracc.acc_id) + ", '" + dbracc.phone + "') ");
}
void ReaderAccountRepository::updateAccount(std::shared_ptr<Session<>> session, std::shared_ptr<ReaderAccount> account)
{
    AccountRepository ar;
    ar.updateAccount(session, account->getAccount());

    session->exec("update ReaderAccount set phone = '" + account->getPhone() + "' " +
                  "where acc_id = " + std::to_string(account->getAccount()->getID()));

}
void ReaderAccountRepository::removeAccount(std::shared_ptr<Session<>> session, int id)
{
    std::string q = "delete from ReaderAccount "
                    "where acc_id = " + std::to_string(id);
    session->exec(q);
    AccountRepository repository;
    repository.removeAccount(session, id);
}