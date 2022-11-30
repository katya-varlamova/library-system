cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 17)
project(src)

find_package(SOCI REQUIRED)
find_package(PostgreSQL REQUIRED)
# find_package(MySQL REQUIRED)

find_package(oatpp REQUIRED)
find_package(oatpp-swagger REQUIRED)
find_package(jwt-cpp REQUIRED)
include(FindPkgConfig)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(LibreSSL 3.0.0 REQUIRED)
find_package(oatpp-libressl 1.3.0 REQUIRED)

set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})

if(APPLE)
add_library(jsoncpp SHARED IMPORTED)
set_target_properties(jsoncpp PROPERTIES
               IMPORTED_LOCATION "/usr/local/Cellar/jsoncpp/1.9.4_1/lib/libjsoncpp.24.dylib"
               INTERFACE_INCLUDE_DIRECTORIES "/usr/local/Cellar/jsoncpp/1.9.4_1/include/json"
               )
else()
    find_package(jsoncpp CONFIG REQUIRED)
    get_target_property(JSON_INC_PATH jsoncpp_lib INTERFACE_INCLUDE_DIRECTORIES)
    include_directories(${JSON_INC_PATH})
endif()
#add_library(jsoncpp SHARED IMPORTED)
#set_target_properties(jsoncpp PROPERTIES
#        IMPORTED_LOCATION "/usr/local/Cellar/jsoncpp/1.9.4_1/lib/libjsoncpp.24.dylib"
#        INTERFACE_INCLUDE_DIRECTORIES "/usr/local/Cellar/jsoncpp/1.9.4_1/include/json"
#        )
add_subdirectory(Database)
add_subdirectory(Logger)
add_subdirectory(Logic)
add_subdirectory(test)
add_subdirectory(main)
