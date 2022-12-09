cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 17)
project(bench)


add_executable(bench
        bench.cpp
        )

target_compile_definitions(bdbench  PUBLIC TEST_CONFIGURATION=2)
#target_compile_definitions(test  PUBLIC TEST_CONFIGURATION=1)
target_link_libraries(bench bl bdbench logger ${Boost_LIBRARIES})
