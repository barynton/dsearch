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

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(core
    PRIVATE
        gcov
    )

    target_compile_options(core PRIVATE -O0 -fprofile-arcs -ftest-coverage -fno-elide-constructors -fno-default-inline)
endif()