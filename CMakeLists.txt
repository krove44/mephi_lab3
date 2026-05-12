cmake_minimum_required(VERSION 3.28)
project(third_laba)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# enable_testing()

# include(FetchContent)

# FetchContent_Declare(googletest
#     URL https://github.com/google/googletest/archive/refs/heads/main.zip
# )

# FetchContent_MakeAvailable(googletest)

# add_executable(tests
#     tests/tests.cpp
# )

# target_link_libraries(tests PRIVATE gtest gtest_main)

# include(GoogleTest)
# gtest_discover_tests(tests)

set(PDCURSES_DIR "C:/Users/krove44/Desktop/PDCurses-3.9")

add_executable(ui
    main.cpp
)

target_include_directories(ui PRIVATE
    ${PDCURSES_DIR}
)

target_link_libraries(ui PRIVATE
    ${PDCURSES_DIR}/wincon/pdcurses.a
    -lwinmm
)