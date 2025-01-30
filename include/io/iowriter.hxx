#ifndef IOWRITER_TPP
#define IOWRITER_TPP

#include "ioreader.hxx"
#include <regex>

// Класс для записи файлов
class IOWriter : public IO {
public:
    explicit IOWriter(std::string_view fname) : IO(fname) {}

    /// @brief Создать новый пустой файл с указанным именем пакета
    /// @param packageName Имя пакета (только маленькие буквы и `_`)
    /// @return void или ошибка
    [[nodiscard]] std::expected<void, IOError> create(std::string_view packageName) noexcept {
        if (!isValidPackageName(packageName)) {
            return std::unexpected(IOError::InvalidFormat);
        }

        try {
            std::ofstream file(filepath);
            if (!file) return std::unexpected(IOError::WriteError);

            file << "package " << packageName << '\n';
            return {};
        } catch (...) {
            return std::unexpected(IOError::WriteError);
        }
    }

    /// @brief Записать данные в файл, сохраняя пакет
    /// @param packageName Имя пакета (только маленькие буквы и `_`)
    /// @param data Данные для записи
    /// @return void или ошибка
    template<std::ranges::input_range R>
        requires std::convertible_to<std::ranges::range_value_t<R>, std::string_view>
    [[nodiscard]] std::expected<void, IOError> write(std::string_view packageName, R&& data) noexcept {
        if (!isValidPackageName(packageName)) {
            return std::unexpected(IOError::InvalidFormat);
        }

        try {
            std::ofstream file(filepath);
            if (!file) return std::unexpected(IOError::WriteError);

            file << "package " << packageName << '\n';

            for (const auto& str : data) {
                file << str << '\n';
            }

            return {};
        } catch (...) {
            return std::unexpected(IOError::WriteError);
        }
    }

    /// @brief Добавить строку в конец файла, сохраняя пакет
    /// @param str Строка для добавления
    /// @return void или ошибка
    [[nodiscard]] std::expected<void, IOError> append(std::string_view str) noexcept {
        IOReader reader(filepath.string());
        auto packageName = reader.getPackageName();
        if (!packageName) return std::unexpected(packageName.error());

        auto data = reader.read();
        if (!data) return std::unexpected(data.error());

        data->push_back(std::string(str));
        return write(*packageName, *data);
    }

private:
    /// @brief Проверка корректности имени пакета
    /// @param name Имя пакета
    /// @return true, если имя валидное
    [[nodiscard]] static bool isValidPackageName(std::string_view name) noexcept {
        static const std::regex packageRegex(R"(^[a-z_]+$)");
        return std::regex_match(name.begin(), name.end(), packageRegex);
    }
};
#endif /* IOWRITER_TPP */
