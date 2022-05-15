//
// Created by Екатерина on 10.05.2022.
//

#ifndef SRC_LIBRARIANACCOUNTREPOSITORY_H
#define SRC_LIBRARIANACCOUNTREPOSITORY_H


#include "../../../Connection/Session.h"
#include "../../../../Logic/Entities/Account/LibrarianAccount.h"
#include "DBLibrarianAccount.h"
#include "LibrarianAccountConverter.h"
#include "../AccountSpecifications/GetAccount.h"
#include "../AccountFilters/ByAccountIDFilter.h"
#include "../../DBLibrary/LibrarySpecifications/LibarySpecification.h"
#include "../../DBLibrary/LibrarySpecifications/GetLibrary.h"
#include "../../DBLibrary/LibraryFilters/ByLibraryIDFilter.h"
#include "../../DBLibrary/LibraryFilters/ByAddressFilter.h"
#include "../../DBLibrary/LibraryFilters/ByLibraryNameFilter.h"
#include "../../DBLibrary/LibraryRepository.h"
#include "../AccountRepository.h"
#include "LibrarianAccountSpecifications/LibrarianAccountSpecification.h"
class LibrarianAccountRepository {
public:
    void addAccount(std::shared_ptr<Session> session, std::shared_ptr<LibrarianAccount> account);
    void removeAccount(std::shared_ptr<Session> session, int id);
    void updateAccount(std::shared_ptr<Session> session, std::shared_ptr<LibrarianAccount> account);

    std::vector<std::shared_ptr<LibrarianAccount>> query(std::shared_ptr<Session> session, std::shared_ptr<LibrarianAccountSpecification> specification);
};

#endif //SRC_LIBRARIANACCOUNTREPOSITORY_H
