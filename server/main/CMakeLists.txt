cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 17)
project(main)


add_executable(main
        main.cpp
        )

target_link_libraries(main bl bdrun logger)
