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


// Класс для тестирования с публичными методами
class TestableApplication {
public:
    static int validate_base(std::string base){
        if (base=="2"|base=="8"|base=="10"|base=="16") return 0;
        else return 1;
    }
    
  
    static int validate_number(std::string number , std::string base_str){

        int result = 0;
        int base  = std::stoi(base_str);
        for (char c : number)
        {
            int digit ; 
            
            if (c >= '0' && c <= '9') digit =  c - '0';
            if (c >= 'A' && c <= 'F') digit =  10 + (c - 'A');
           // std::cout << "digit=" ;
           // std::cout << digit ; 
           // std::cout << " base=" + base_str + "\n";
            if (digit  > base)
            {
                result = 1;
            }
            
        }
        return result;
    }
    
    static std::string toDecimal(std::string number, std::string base) {
        int result = 0;
        int len = number.length();
        int b = std::stoi(base);
        
        for (int i = 0; i < len; i++) {
            char c = number[i];
            int digit = 0;
            
            if (c >= '0' && c <= '9') {
                digit = c - '0';
            } else if (c >= 'A' && c <= 'Z') {
                digit = c - 'A' + 10;
            } else if (c >= 'a' && c <= 'z') {
                digit = c - 'a' + 10;
            }
            
            result += digit * std::pow(b, len - 1 - i);
        }
        
        return std::to_string(result);
    }
    
    static std::string decimalTo16(std::string number) {
        int n = std::stoi(number);
        if (n == 0) return "0";
        std::string result = "";
        char chars16[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
        
        while (n > 0) {
            int ost = n % 16;
            result += chars16[ost];
            n = n / 16;
        }
        
        std::reverse(result.begin(), result.end());
        return result;
    }
    
    static std::string decimalTo_2_8(std::string number, std::string base) {
        int n = std::stoi(number);
        if (n == 0) return "0";
        std::string result = "";
        int b = std::stoi(base);
        
        while (n > 0) {
            int ost = n % b;
            result += std::to_string(ost);
            n = n / b;
        }
        
        std::reverse(result.begin(), result.end());
        return result;
    }
};



TEST_CASE("Тестирование validate_base - положительные результаты") {
    SUBCASE("Проверка корректных систем счисления") {
        CHECK(TestableApplication::validate_base("2") == 0);
    }
}

TEST_CASE("Тестирование validate_base - отрицательные результаты") {
    SUBCASE("Проверка некорректных систем счисления") {
        CHECK(TestableApplication::validate_base("3") == 1);
    }
}



TEST_CASE("Тестирование validate_number - положительные результаты") {
    SUBCASE("Проверка корректных чисел для вернуюю систему счисления") {
        CHECK(TestableApplication::validate_number("1010", "2") == 0);
        CHECK(TestableApplication::validate_number("ABC", "16") == 0);
    }
}

TEST_CASE("Тестирование validate_number - отрицательные результаты") {
    SUBCASE("Проверка некорректных чисел для двоичной системы") {
        CHECK(TestableApplication::validate_number("10A", "2") == 1);

    }    
}



TEST_CASE("Тестирование toDecimal - положительные результаты") {
    SUBCASE("Перевод из шестнадцатеричной системы в десятичную") {
        CHECK(TestableApplication::toDecimal("FF", "16") == "255");
    }
}




TEST_CASE("Тестирование decimalTo16 - положительные результаты") {
    SUBCASE("Перевод десятичных чисел в шестнадцатеричные") {
        CHECK(TestableApplication::decimalTo16("256") == "100");
    }
}

TEST_CASE("Тестирование decimalTo16 - отрицательные результаты") {
    SUBCASE("Проверка некорректных входных данных") {
        CHECK(TestableApplication::decimalTo16("-1") != "1");
    }
}


