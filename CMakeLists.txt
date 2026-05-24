cmake_minimum_required(VERSION 3.28)
project(third_laba)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

enable_testing()

include(FetchContent)
FetchContent_Declare(googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(tests
    tests/VectorTests.cpp
    tests/MatrixTests.cpp
)
target_link_libraries(tests PRIVATE gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)

set(SFML_DIR "C:/msys64/mingw64/lib/cmake/SFML")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(new_main 
    new_main.cpp
    TrajectoryCalculation.cpp
    )
target_link_libraries(new_main PRIVATE SFML::Graphics SFML::Window SFML::System)

add_custom_command(TARGET new_main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:new_main>/assets"
)
