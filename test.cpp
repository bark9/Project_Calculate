/**
 * @file tests.cpp
 * @brief Модульные тесты для конвертера систем счисления с использованием doctest
 * @version 1.0
 * @date 2026-06-17
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <string>
#include <cmath>
#include <algorithm>
#include "functions.cpp"



TEST_CASE("Тестирование function_validate_base - положительные результаты") {
    SUBCASE("Проверка корректных систем счисления") {
        CHECK(function_validate_base("2") == 0);
        CHECK(function_validate_base("8") == 0);
        CHECK(function_validate_base("10") == 0);
        CHECK(function_validate_base("16") == 0);
  
}
}

TEST_CASE("Тестирование function_validate_base - отрицательные результаты") {
    SUBCASE("Проверка некорректных систем счисления") {
        CHECK(function_validate_base("3") == 1);
        CHECK(function_validate_base("0") == 1);
        CHECK(function_validate_base("11") == 1);
        CHECK(function_validate_base("-1") == 1);
    }
}



TEST_CASE("Тестирование validate_number") {
    SUBCASE("Положительные результаты проверка проверка соотвествия числа и СС") {
        CHECK(function_validate_number("1010", "2") == 0);
        CHECK(function_validate_number("76543210", "8") == 0);
        CHECK(function_validate_number("9876543210", "10") == 0);
        CHECK(function_validate_number("FECDA987654321", "16") == 0);
    }

    SUBCASE("ОТрицательные результаты проверка соотвествия числа и СС") {
        CHECK(function_validate_number("10A", "2") == 1);
        CHECK(function_validate_number("-1", "2") == 1);
        CHECK(function_validate_number("876543210", "8") == 1);
        CHECK(function_validate_number("A9876543210", "10") == 1);
        CHECK(function_validate_number("GFECDA987654321", "16") == 1);
    }

}




TEST_CASE("Тестирование toDecimal") {
    SUBCASE("Положительные кейсы Перевод из шестнадцатеричной системы в десятичную") {
        CHECK(function_toDecimal("111", "2") == "7");
        CHECK(function_toDecimal("101", "8") == "65");
        CHECK(function_toDecimal("11", "10") == "11");
        CHECK(function_toDecimal("FF", "16") == "255");
    }
}

TEST_CASE("Тестирование decimalTo16 - положительные результаты") {
    SUBCASE("Перевод десятичных чисел в шестнадцатеричные") {
        CHECK(function_decimalTo16("256") == "100");
        CHECK(function_decimalTo16("16") == "10");
        CHECK(function_decimalTo16("15") == "F");
    }
}

TEST_CASE("Тестирование decimalTo16 - отрицательные результаты") {
    SUBCASE("Проверка некорректных входных данных") {
        CHECK(function_decimalTo16("-1") != "1");
    }
}

TEST_CASE("Тестирование function_decimalTo_2_8 - положительные результаты") {
    SUBCASE("Перевод десятичных чисел в шестнадцатеричные") {
        CHECK(function_decimalTo_2_8("100", "2") == "1100100");
        CHECK(function_decimalTo_2_8("100", "8") == "144");
    }
}

TEST_CASE("Тестирование function_convert") {
    SUBCASE("Перевод десятичных чисел в шестнадцатеричные") {
        CHECK(function_convert("15", "10" , "16") == "F");
        CHECK(function_convert("100", "8", "2") == "1000000");
    }
}


