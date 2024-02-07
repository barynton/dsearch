cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

add_executable(test_core
    main.cpp
    TestDuplicateSearch.cpp
)

add_dependencies(test_core core)

target_link_libraries(test_core 
PRIVATE
    core    
    CONAN_PKG::catch2
)

include(Catch)

#https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md
catch_discover_tests(test_core)
