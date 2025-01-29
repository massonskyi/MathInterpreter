#ifndef IO_HXX_
#define IO_HXX_

#include <string>
#include <string_view>
#include <vector>
#include <expected>
#include <span>
#include <concepts>
#include <filesystem>
#include <fstream>
#include <format>

enum class IOError {
    FileNotFound,
    InvalidFormat,
    WriteError,
    ReadError
};

class IO {
protected:
    std::filesystem::path filepath;

    IO(std::string_view fname) : filepath(fname) {}
    IO() = default;
};

#endif /* IO_HXX_ */