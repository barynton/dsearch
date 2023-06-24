cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

add_executable(test_core
    main.cpp
    test.cpp
)

add_dependencies(test_core core)

target_compile_definitions(test_core 
PRIVATE 
-DCATCH_CONFIG_ENABLE_BENCHMARKING
)

target_link_libraries(test_core 
PRIVATE
    core    
    CONAN_PKG::catch2
)

add_test(NAME core COMMAND test_core)