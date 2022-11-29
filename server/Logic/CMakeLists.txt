cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_STANDARD 17)
project(bl)

add_library(bl
        Entities/EBook/EBook.cpp
        Entities/Book/Book.cpp
        Entities/Library/Library.cpp
        Entities/Account/Account.cpp
        DataAccessManager/DataAccessManager.cpp
        Entities/Account/LibrarianAccount.cpp
        Entities/Account/ReaderAccount.cpp
        Entities/Account/AdminAccount.cpp
        Configuration/FileConfiguration.cpp
        Server/Controller/JWTAuth.cpp
        Server/Controller/JWTAuth.h
        DataAccessManager/DataAccessManagerRest.cpp
        )
target_include_directories(bl PUBLIC {CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(bl PUBLIC OATPP_SWAGGER_RES_PATH="${OATPP_BASE_DIR}/bin/oatpp-swagger/res")
target_compile_definitions(bl PUBLIC CERT_CRT_PATH="/Users/kate/Desktop/testing/src/WebClient/https/localhost.crt")
target_compile_definitions(bl PUBLIC CERT_PEM_PATH="/Users/kate/Desktop/testing/src/WebClient/https/localhost.key")
set_target_properties(jsoncpp PROPERTIES
        IMPORTED_LOCATION "/usr/local/lib/libjsoncpp.so.25"
        INTERFACE_INCLUDE_DIRECTORIES "/usr/local/include/json"
        )
target_link_libraries(bl SOCI::soci_core PostgreSQL::PostgreSQL oatpp::oatpp oatpp::oatpp-swagger jsoncpp jwt-cpp::jwt-cpp oatpp::oatpp-libressl LibreSSL::TLS LibreSSL::SSL LibreSSL::Crypto)