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
 * @class Event
 * @brief Класс для хранения информации о событии конвертации
 *
 * Хранит данные о выполненной операции конвертации числа:
 * - время выполнения
 * - исходное число
 * - исходная система счисления
 * - целевая система счисления
 * - результат конвертации
 */
class Event {
public:
  std::string dt;        ///< Время выполнения операции в формате DT=дд.мм.гггг TM=чч:мм:сс
  std::string number;    ///< Исходное число для конвертации
  std::string source_nn; ///< Исходная система счисления (2, 8, 10, 16)
  std::string target_nn; ///< Целевая система счисления (2, 8, 10, 16)
  std::string result;    ///< Результат конвертации

  /**
   * @brief Формирует строковое представление события
   * @return Строка, содержащая все данные события через пробел
   */
  std::string getStringLine() {
    return dt + " " + number + " " + source_nn + " " + target_nn + " " + result;
  }
};

/**
 * @class Time
 * @brief Класс для работы с временем
 *
 * Предоставляет статический метод для получения текущего времени
 * в формате DT=дд.мм.гггг TM=чч:мм:сс
 */
class Time {
public:
  /**
   * @brief Получает текущее время в строковом формате
   * @return Строка с текущим временем в формате DT=дд.мм.гггг TM=чч:мм:сс
   */
  static std::string getStringTime() {
    time_t mytime = time(NULL);
    struct tm *ltm = localtime(&mytime);

    std::string ss = "DT=";
    ss += std::to_string(ltm->tm_mday) + ".";
    ss += std::to_string(ltm->tm_mon + 1) + ".";
    ss += std::to_string(ltm->tm_year + 1900) + " TM=";
    ss += std::to_string(ltm->tm_hour) + ":";
    ss += std::to_string(ltm->tm_min) + ":";
    ss += std::to_string(ltm->tm_sec);

    return ss;
  }
};

/**
 * @class History
 * @brief Класс для управления историей операций
 *
 * Обеспечивает хранение, загрузку и сохранение истории
 * выполненных операций конвертации
 */
class History {
  std::vector<Event> arrayEvents; ///< Вектор для хранения событий
  std::string fileName;           ///< Имя файла для хранения истории

public:
  /**
   * @brief Конструктор класса History
   *
   * Инициализирует имя файла и загружает историю из файла
   */
  History() {
    fileName = "history.txt";
    loadFromFile();
  }

  /**
   * @brief Добавляет событие в историю
   * @param event Событие для добавления
   */
  void addToHistory(Event event) { arrayEvents.push_back(event); }

  /**
   * @brief Сохраняет историю в файл
   *
   * Перезаписывает файл с историей, записывая все события
   */
  void saveToFile() {
    try {
      std::ofstream file(fileName, std::ios::trunc);
      if (!file.is_open())
        return;

      for (int i = 0; i < arrayEvents.size(); i++) {
        file << arrayEvents[i].getStringLine() << "\n";
      }
      file.close();
    } catch (...) {
      std::cout << "Error";
    };
  }

  /**
   * @brief Загружает историю из файла
   *
   * Читает файл истории и восстанавливает все сохраненные события
   */
  void loadFromFile() {
    std::ifstream file(fileName);
    if (!file.is_open())
      return;

    std::string line;
    while (std::getline(file, line)) {
      Event e;
      std::stringstream ss(line);

      std::string token;
      int i = 0;
      while (getline(ss, token, ' ')) {
        if (i == 0)
          e.dt = token;
        if (i == 1)
          e.number = token;
        if (i == 2)
          e.source_nn = token;
        if (i == 3)
          e.target_nn = token;
        if (i == 4)
          e.result = token;
        i++;
      }
      addToHistory(e);
    }
    file.close();
  }

  /**
   * @brief Выводит всю историю на экран
   * Отображает все сохраненные события в консоли
   */
  void listHistory() {
    for (int i = 0; i < arrayEvents.size(); i++) {
      std::cout << arrayEvents[i].getStringLine() << "\n";
    }
  }
};

/**
 * @class Application
 * @brief Главный класс приложения
 *
 * Управляет работой калькулятора систем счисления,
 * включает логику конвертации и взаимодействие с пользователем
 */
class Application {
private:
  History history; ///< Объект для управления историей операций

  /**
   * @brief Проверяет корректность системы счисления
   * @param base Строковое представление системы счисления
   * @return 0 если корректно, 1 если нет
   */
  int validate_base(std::string base) {
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
  int validate_number(std::string number, std::string base_str) {
    int result = 0;
    int base = std::stoi(base_str);
    for (char c : number) {
      int digit;

      if (c >= '0' && c <= '9')
        digit = c - '0';
      if (c >= 'A' && c <= 'F')
        digit = 10 + (c - 'A');

      if (digit > base) {
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
  std::string decimalTo16(std::string number) {
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
  std::string decimalTo_2_8(std::string number, std::string base) {
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
  std::string toDecimal(std::string number, std::string base) {
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
   * @brief Основной метод конвертации
   *
   * Запрашивает у пользователя исходные данные,
   * выполняет конвертацию и сохраняет результат
   */
  void convert() {
    std::string base;
    std::cout << "Enter base number(2,8,10,16):\n";
    std::cin >> base;

    while (validate_base(base) == 1) {
      std::cout << "Error base number! Enter base number(2,8,10,16):\n";
      std::cin >> base;
    }

    std::string number;
    std::cout << "Enter culcalate number:\n";
    std::cin >> number;

    while (validate_number(number, base) == 1) {
      std::cout << "Error number! Enter number in base " + base + "\n";
      std::cin >> number;
    }

    std::string num = toDecimal(number, base);

    std::string base_target;
    std::cout << "Enter base number(2,8,10,16):\n";
    std::cin >> base_target;

    while (validate_base(base_target) == 1) {
      std::cout << "Error base number! Enter base number(2,8,10,16):\n";
      std::cin >> base_target;
    }

    std::string result = "";
    if (base_target == "16")
      result = decimalTo16(num);
    else
      result = decimalTo_2_8(num, base_target);
    std::cout << "Result = " + result + "\n";

    Event ev;
    Time t;
    ev.dt = t.getStringTime();
    ev.number = number;
    ev.source_nn = base;
    ev.target_nn = base_target;
    ev.result = result;
    history.addToHistory(ev);
    history.saveToFile();
  }

  /**
   * @brief Показывает историю операций
   */
  void showHistory() { history.listHistory(); }

  /**
   * @brief Отображает меню приложения
   */
  void showMenu() {
    std::cout << "Menu Calculator\n";
    std::cout << "  1. calculate number\n";
    std::cout << "  2. history\n";
    std::cout << "  3. exit\n";
  }

public:
  /**
   * @brief Конструктор класса Application
   */
  Application() : history() {}

  /**
   * @brief Запускает основный цикл приложения
   *
   * Отображает меню и обрабатывает выбор пользователя
   */
  void run() {
    bool running = true;

    while (running) {
      try {
        showMenu();
        int choice;
        std::cout << "Enter number menu: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
          convert();
          break;
        case 2:
          showHistory();
          break;
        case 3:
          running = false;
          std::cout << "\n";
          break;
        default:
          std::cout << "Error choice menu. Must be 1,2,3\n";
        }
      } catch (...) {
        std::cout << "Error!!!";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
      }
    }
  }
};

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении
 */
int main() {
  try {
    Application app;
    app.run();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}