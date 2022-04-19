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
class BookDto : public oatpp::DTO {
    DTO_INIT(BookDto, DTO)

    DTO_FIELD(String, name);
    DTO_FIELD(String, author);
    DTO_FIELD(String, library_name);
    DTO_FIELD(String, library_address);
};

class BooksDto : public oatpp::DTO {
    DTO_INIT(BooksDto, DTO)

    DTO_FIELD(Vector<Object<BookDto>>, books);
};

class AccountDto : public oatpp::DTO {
    DTO_INIT(AccountDto, DTO)

    DTO_FIELD(String, name);
    DTO_FIELD(String, login);
    DTO_FIELD(String, password);
    DTO_FIELD(String, role);
};

#include OATPP_CODEGEN_END(DTO)


#endif //SRC_DTOS_H
