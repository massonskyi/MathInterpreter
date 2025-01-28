#ifndef STRINGVALIDATOR_HPP
#define STRINGVALIDATOR_HPP


#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <sstream>

class StringValidator {
public:
    struct Error {
        std::string type;
        std::string message;
        size_t position;
        std::string context; // Строка с контекстом ошибки
    };
    using err_msg = std::vector<Error>;
    StringValidator() = default;

    // Метод для валидации строки
    bool validate(const std::string& input) {
        clearErrors();

        // Проверка пробелов вокруг '='
        size_t equalPos = input.find("=");
        if (equalPos != std::string::npos &&
            (equalPos == 0 || input[equalPos - 1] != ' ' || input[equalPos + 1] != ' ')) {
            _M_add("MissingSpacesAroundEqual", "Отсутствуют пробелы до или после '='.", equalPos, input);
        }
        // Проверка на незакрытые скобки
        if (!_M_has_balanced_brackets(input)) {
            _M_add("UnbalancedBrackets", "Количество открытых и закрытых скобок не совпадает.", input.find("["), input);
        }

        return _M_errors.empty();
    }

    // Получить ошибки
    const err_msg& getErrors() const {
        return _M_errors;
    }

    // Очистить ошибки
    void clearErrors() {
        _M_errors.clear();
    }

    // Печать ошибок с цветом
    void printErrors() const {
        for (const auto& error : _M_errors) {
            std::cout << "\033[31m"; // Устанавливаем красный цвет
            std::cout << "  File \"" << __FILE__ << "\", line " << __LINE__ << "\n"; // Выводим имя файла и строку
            std::cout << "    " << error.context << "\n";

            // Строим стрелочку, которая указывает на ошибку
            std::cout<< "    ";
            for (size_t i = 0; i < error.position; ++i) {
                std::cout << "="; // Выводим пробелы до позиции ошибки
            }

            std::cout << "^^"; // Индикатор ошибки
            std::cout << "\n";

            std::cout << "SyntaxError: " << error.message << "\n";
            std::cout << "\033[0m"; // Сброс цвета
        }
    }


private:


    err_msg _M_errors;

    // Добавление ошибки в список
    void _M_add(const std::string& type, const std::string& message, size_t position, const std::string& input) {
        std::string context = _M_set_context(position, input);
        _M_errors.push_back({type, message, position, context});
    }

    // Генерация контекста ошибки (строка, где произошла ошибка)
    std::string _M_set_context(size_t position, const std::string& input) {
        size_t start = position > 10 ? position - 10 : 0; // Начало контекста (не менее 10 символов)
        size_t end = position + 10 < input.length() ? position + 10 : input.length(); // Конец контекста

        return input.substr(start, end - start); // Возвращаем часть строки вокруг ошибки
    }

    // Проверка на сбалансированные скобки
    bool _M_has_balanced_brackets(const std::string& input) {
        int balance = 0;
        for (size_t i = 0; i < input.size(); ++i) {
            char ch = input[i];
            if (ch == '[') {
                ++balance;
            } else if (ch == ']') {
                --balance;
            }

            if (balance < 0) {
                return false; // Закрывающая скобка без открывающей
            }
        }
        return balance == 0;
    }


};
#endif /* STRINGVALIDATOR_HPP */