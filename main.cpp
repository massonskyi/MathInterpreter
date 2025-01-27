#include <iostream>
#include <regex>
#include <vector>
#include <utility> // для std::pair

int main() {
    // Пример строки
    std::string input_string = "fn my_function (let x: i32, let y: f64) -> i32 {};";

    // Регулярное выражение для извлечения имени функции, аргументов и типа возвращаемого значения
    std::regex pattern(R"(fn\s+(\w+)\s*\((.*?)\)\s*->\s*(\w+)\s*\{.*?\};)");

    // Поиск совпадений
    std::smatch match;
    if (std::regex_match(input_string, match, pattern)) {
        std::string function_name = match[1]; // Имя функции
        std::string args_str = match[2];      // Аргументы как строка
        std::string return_type = match[3];   // Тип возвращаемого значения

        // Регулярное выражение для извлечения аргументов
        std::regex arg_pattern(R"(let\s+(\w+)\s*:\s*(\w+))");
        std::smatch arg_match;
        std::string::const_iterator args_start(args_str.cbegin());
        std::vector<std::pair<std::string, std::string>> parsed_args;

        // Обработка аргументов
        while (std::regex_search(args_start, args_str.cend(), arg_match, arg_pattern)) {
            std::string arg_name = arg_match[1];  // Имя аргумента
            std::string arg_type = arg_match[2];  // Тип аргумента
            parsed_args.emplace_back(arg_name, arg_type);
            args_start = arg_match.suffix().first; // Переход к следующему аргументу
        }

        // Вывод результатов
        std::cout << "Function Name: " << function_name << std::endl;
        std::cout << "Arguments: ";
        for (const auto& arg : parsed_args) {
            std::cout << "(" << arg.first << ": " << arg.second << ") ";
        }
        std::cout << std::endl;
        std::cout << "Return Type: " << return_type << std::endl;
    } else {
        std::cout << "No match found!" << std::endl;
    }

    return 0;
}