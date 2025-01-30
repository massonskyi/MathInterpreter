//
// Created by massonskyi on 28.01.25.
//
#include "../include/utils.hxx"

std::string to_lower(const std::string& s) {
    std::string result;
    std::transform(s.begin(), s.end(), std::back_inserter(result),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
}

std::string remove_whitespaces(const std::string &str)
{
    std::string result;
    std::for_each(str.begin(), str.end(), [&](char c)
    {
        if (!std::isspace(c)) {
            result.push_back(c);
        } });

    return result;
}