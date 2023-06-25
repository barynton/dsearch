cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

add_executable(dsearch
    main.cpp
)

add_dependencies(dsearch core)

target_link_libraries(dsearch 
PRIVATE
    core
    CONAN_PKG::cli11
)