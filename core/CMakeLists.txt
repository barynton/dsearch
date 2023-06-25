cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

add_library(core
    DirectoryScan.cpp
    DirectoryGroupScan.cpp

)

target_include_directories(core 
PUBLIC
    ./include
)

target_link_libraries(core
PRIVATE
    CONAN_PKG::xxhash
)