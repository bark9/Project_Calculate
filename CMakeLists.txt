cmake_minimum_required(VERSION 3.10)
project(NumberConverter)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основной исполняемый файл
add_executable(converter main.cpp)
target_compile_options(converter PRIVATE -Wall -Wextra)

# Тесты
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    # Проверяем наличие doctest.h в папке external
    set(DOCTEST_DIR ${CMAKE_SOURCE_DIR}/external)
    set(DOCTEST_HEADER ${DOCTEST_DIR}/doctest.h)
    
    #if(NOT EXISTS ${DOCTEST_HEADER})
    #    message(WARNING "doctest.h not found in ${DOCTEST_DIR}")
    #    message(WARNING "Please download doctest.h from https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h")
    #    message(WARNING "And place it in ${DOCTEST_DIR}")
    #else()
        # Создаем таргет для тестов
        add_executable(tests test.cpp)
        target_include_directories(tests PRIVATE ${DOCTEST_DIR})
        target_compile_options(tests PRIVATE -Wall -Wextra)
        
        enable_testing()
        add_test(NAME NumberConverterTests COMMAND tests)
    #endif()
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")