//
// Created by Екатерина on 18.04.2022.
//

#ifndef SRC_DTOS_H
#define SRC_DTOS_H


#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class LibraryDto: public oatpp::DTO {
    DTO_INIT(LibraryDto, DTO)
    DTO_FIELD(Int64, id);
    DTO_FIELD(String, name);
    DTO_FIELD(String, address);
};
class BookDto : public oatpp::DTO {
    DTO_INIT(BookDto, DTO)
    DTO_FIELD(Int64, id);
    DTO_FIELD(String, name);
    DTO_FIELD(String, author);
    DTO_FIELD(Int64, lib_id);
    DTO_FIELD(String, login);
};

class BooksDto : public oatpp::DTO {
    DTO_INIT(BooksDto, DTO)

    DTO_FIELD(Vector<Object<BookDto>>, books);
};

class EBookDto : public oatpp::DTO {
    DTO_INIT(EBookDto, DTO)
    DTO_FIELD(Int64, id);
    DTO_FIELD(String, name);
    DTO_FIELD(String, author);
    DTO_FIELD(String, link);
};

class EBooksDto : public oatpp::DTO {
    DTO_INIT(EBooksDto, DTO)

    DTO_FIELD(Vector<Object<EBookDto>>, books);
};
class LibrarianAccountDTO : public oatpp::DTO {
    DTO_INIT(LibrarianAccountDTO, DTO)
    DTO_FIELD(Int64, lib_id);
};
class ReaderAccountDTO : public oatpp::DTO {
    DTO_INIT(ReaderAccountDTO, DTO)
    DTO_FIELD(String, phone);
};
class AdminAccountDTO : public oatpp::DTO {
    DTO_INIT(AdminAccountDTO, DTO)
};
class AccountDto : public oatpp::DTO {
    DTO_INIT(AccountDto, DTO)

    DTO_FIELD(Int64, id);
    DTO_FIELD(String, name);
    DTO_FIELD(String, token);
    DTO_FIELD(Object<AdminAccountDTO>, admin_acc);
    DTO_FIELD(Object<LibrarianAccountDTO>, librarian_acc);
    DTO_FIELD(Object<ReaderAccountDTO>, reader_acc);
};

class LibrariesDto : public oatpp::DTO {
    DTO_INIT(LibrariesDto, DTO)

    DTO_FIELD(Vector<Object<LibraryDto>>, libraries);
};

#include OATPP_CODEGEN_END(DTO)


#endif //SRC_DTOS_H
