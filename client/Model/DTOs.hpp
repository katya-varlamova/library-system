
#ifndef DemoApiModels_hpp
#define DemoApiModels_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

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
    DTO_FIELD(String, login);
    DTO_FIELD(String, password);
    DTO_FIELD(String, role);
    DTO_FIELD(Object<AdminAccountDTO>, admin_acc);
    DTO_FIELD(Object<LibrarianAccountDTO>, librarian_acc);
    DTO_FIELD(Object<ReaderAccountDTO>, reader_acc);
};

class LibrariesDto : public oatpp::DTO {
    DTO_INIT(LibrariesDto, DTO)

    DTO_FIELD(Vector<Object<LibraryDto>>, libraries);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* DemoApiModels_hpp */
