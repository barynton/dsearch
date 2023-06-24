cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

add_executable(cli
    main.cpp
)

add_dependencies(cli core)

target_link_libraries(cli 
PRIVATE
    core
    CONAN_PKG::cli11
)