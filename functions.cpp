#include <algorithm>
#include <climits>
#include <cmath>
#include <cctype>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>  
  
  
  /**
   * @brief Проверяет корректность системы счисления
   * @param base Строковое представление системы счисления
   * @return 0 если корректно, 1 если нет
   */
  int function_validate_base(std::string base) {
    if (base == "2" || base == "8" || base == "10" || base == "16")
      return 0;
    else
      return 1;
  }


  /**
   * @brief Проверяет корректность числа для заданной системы счисления
   * @param number Проверяемое число
   * @param base_str Система счисления в виде строки
   * @return 0 если корректно, 1 если нет
   */
  int function_validate_number(std::string number, std::string base_str) {
    int result = 0;
    int base = std::stoi(base_str);
    for (char c : number) {
      if (c=='-') result = 1;
      int digit;

      if (c >= '0' && c <= '9')
        digit = c - '0';

      if (c >= 'A')
        digit = 10 + (c - 'A');

      if (digit >= base) {
        result = 1;
      }
    }
    return result;
  }


   /**
   * @brief Конвертирует десятичное число в шестнадцатеричное
   * @param number Десятичное число в виде строки
   * @return Шестнадцатеричное представление числа
   */
  std::string function_decimalTo16(std::string number) {
    int n = std::stoi(number);
    std::string result = "";
    char chars16[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                      '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    while (n > 0) {
      int ost = n % 16;
      result += chars16[ost];
      n = n / 16;
    }

    reverse(result.begin(), result.end());
    return result;
  }


  /**
   * @brief Конвертирует десятичное число в двоичную или восьмеричную систему
   * @param number Десятичное число в виде строки
   * @param base Целевая система счисления (2 или 8)
   * @return Число в целевой системе счисления
   */
  std::string function_decimalTo_2_8(std::string number, std::string base) {
    int n = std::stoi(number);
    std::string result = "";
    int b = std::stoi(base);

    while (n > 0) {
      int ost = n % b;
      result += std::to_string(ost);
      n = n / b;
    }

    reverse(result.begin(), result.end());
    return result;
  }


    /**
   * @brief Конвертирует число из любой системы в десятичную
   * @param number Число в исходной системе счисления
   * @param base Исходная система счисления
   * @return Десятичное представление числа
   */
  std::string function_toDecimal(std::string number, std::string base) {
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

  /**
   * @brief Конвертирует число из любой системы в любую
   * @param number Число в исходной системе счисления
   * @param base Исходная система счисления
   * @param base_target Исходная система счисления
   * @return Десятичное представление числа
   */
  std::string function_convert(std::string number, std::string base, std::string base_target){
    std::string num = function_toDecimal(number, base);
    std::string result = "";
    if (base_target == "16")
      result = function_decimalTo16(num);
    else
      result = function_decimalTo_2_8(num, base_target);
    return result;
  }