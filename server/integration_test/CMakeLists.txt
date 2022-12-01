cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 17)
project(itest)


add_executable(itest
        itest.cpp
        )

target_compile_definitions(bdrun  PUBLIC TEST_CONFIGURATION=0)
target_link_libraries(itest bl bdrun logger ${Boost_LIBRARIES})