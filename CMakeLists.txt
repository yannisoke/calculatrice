cmake_minimum_required(VERSION 3.16)
project(calculatrice_cli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(calculatrice
    src/main.cpp
    src/calculator.cpp
    src/commands.cpp
    src/history.cpp
)

add_executable(calculatrice_tests
    tests/test_calculator.cpp
    src/calculator.cpp
    src/commands.cpp
    src/history.cpp
)

target_include_directories(calculatrice PRIVATE include)
target_include_directories(calculatrice_tests PRIVATE include)

if (MSVC)
    target_compile_options(calculatrice PRIVATE /W4 /permissive-)
    target_compile_options(calculatrice_tests PRIVATE /W4 /permissive-)
else()
    target_compile_options(calculatrice PRIVATE -Wall -Wextra -pedantic -Wconversion)
    target_compile_options(calculatrice_tests PRIVATE -Wall -Wextra -pedantic -Wconversion)
endif()

# (Optionnel) Intégration CTest
include(CTest)
enable_testing()
add_test(NAME calc_basic_tests COMMAND calculatrice_tests)