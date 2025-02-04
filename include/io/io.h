#ifndef IO_h_
#define IO_h_

#include <string>
#include <string_view>
#include <vector>
#include <span>
#include <concepts>
#include <filesystem>
#include <fstream>

enum class IOError {
    FileNotFound,
    InvalidFormat,
    WriteError,
    ReadError
};

class IO {
protected:
    std::filesystem::path filepath;

    explicit IO(std::string_view fname) : filepath(fname) {}
    IO() = default;
};

#endif /* IO_h_ */