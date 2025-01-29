#ifndef IOREAD_HXX
#define IOREAD_HXX
#include "io.hxx"
#include <regex>
/// @brief Class for reading data from a text file and storing it in a vector of strings
class IOReader : public IO {
public:
    /// @brief Construct the IOReader
    IOReader() = default;
    
    /// @brief Constructor for IOReader class
    explicit IOReader(std::string_view fname) : IO(fname) {}

    /// @brief Check if the file is valid (must start with "package <name>")
    /// @return true if the file is valid, otherwise an error
    [[nodiscard]] std::expected<bool, IOError> isValid() const noexcept {
        try {
            std::ifstream file(filepath);
            if (!file) return std::unexpected(IOError::FileNotFound);

            std::string firstLine;
            if (!std::getline(file, firstLine)) {
                return std::unexpected(IOError::InvalidFormat);
            }

            std::string packageName = extractPackageName(firstLine);
            if (packageName.empty()) {
                return std::unexpected(IOError::InvalidFormat);
            }

            return true;
        } catch (...) {
            return std::unexpected(IOError::ReadError);
        }
    }

    /// @brief Read the package name from the file
    /// @return the package name if valid, otherwise an error
    [[nodiscard]] std::expected<std::string, IOError> getPackageName() const noexcept {
        try {
            std::ifstream file(filepath);
            if (!file) return std::unexpected(IOError::FileNotFound);

            std::string firstLine;
            if (!std::getline(file, firstLine)) {
                return std::unexpected(IOError::InvalidFormat);
            }

            std::string packageName = extractPackageName(firstLine);
            if (packageName.empty()) {
                return std::unexpected(IOError::InvalidFormat);
            }

            return packageName;
        } catch (...) {
            return std::unexpected(IOError::ReadError);
        }
    }

    /// @brief Read data from the file and store it in a vector of strings (excluding package name)
    /// @return vector of strings read from the file
    [[nodiscard]] std::expected<std::vector<std::string>, IOError> read() const noexcept {
        try {
            std::ifstream file(filepath);
            if (!file) return std::unexpected(IOError::FileNotFound);

            std::vector<std::string> data;
            std::string line;

            // Пропускаем первую строку (package <name>)
            if (!std::getline(file, line) || extractPackageName(line).empty()) {
                return std::unexpected(IOError::InvalidFormat);
            }

            while (std::getline(file, line)) {
                data.push_back(std::move(line));
            }

            return data;
        } catch (...) {
            return std::unexpected(IOError::ReadError);
        }
    }

    /// @brief Get the line count in the file (excluding package name)
    /// @return the line count in the file
    [[nodiscard]] std::expected<size_t, IOError> getLineCount() const noexcept {
        try {
            std::ifstream file(filepath);
            if (!file) return std::unexpected(IOError::FileNotFound);

            size_t count = 0;
            std::string line;

            // Пропускаем первую строку
            if (!std::getline(file, line) || extractPackageName(line).empty()) {
                return std::unexpected(IOError::InvalidFormat);
            }

            while (std::getline(file, line)) {
                ++count;
            }

            return count;
        } catch (...) {
            return std::unexpected(IOError::ReadError);
        }
    }

private:
    /// @brief Extract package name from a line
    /// @param line The line containing the package statement
    /// @return Extracted package name or empty string if invalid
    [[nodiscard]] static std::string extractPackageName(const std::string& line) noexcept {
        std::regex packageRegex(R"(^\s*package\s+([a-z_]+))");
        std::smatch match;
        if (std::regex_search(line, match, packageRegex)) {
            return match[1].str(); // Возвращаем найденное имя пакета
        }
        return {};
    }
};
#endif /* IOREAD_HXX */
