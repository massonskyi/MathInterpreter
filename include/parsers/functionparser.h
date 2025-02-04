#ifndef FUNCTION_PARSER_HPP
#define FUNCTION_PARSER_HPP

#include <iostream>
#include <regex>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include "../validators/functionbodyvalidator.h"
class FuncParser final{
public:
    using func_args = std::vector<std::pair<std::string, std::string>>;
        
    struct NewFunction{

        std::string _func_name;
        func_args _args;
        std::string _body;
        std::string _return_type;
    };

    FuncParser() = default;
    ~FuncParser() = default;
    NewFunction parse(const std::string& input_string){
        NewFunction result;
        std::smatch match;

        std::regex pattern(R"(fn\s+(\w+)\s*\((.*?)\)\s*->\s*(\w+)\s*\{([\s\S]*?)\};)");

        if(std::regex_search(input_string, match, pattern)){
        std::string function_name = match[1];
        std::string args_str = match[2];
        std::string return_type = match[3];
        std::string function_body = match[4];

        std::regex arg_pattern(R"(let\s+(\w+)\s*:\s*(\w+))");
        std::smatch arg_match;
        std::string::const_iterator args_start(args_str.cbegin());
        func_args parsed_args;
        
        while (std::regex_search(args_start, args_str.cend(), arg_match, arg_pattern)) {
            parsed_args.emplace_back(arg_match[1], arg_match[2]);
            args_start = arg_match.suffix().first;
        }
        
        result._func_name = function_name;
        result._args = parsed_args;
        result._body = function_body;
        result._return_type = return_type;
        return result;
        }else{
            throw std::runtime_error("Invalid function declaration");
        }
        
    }
private:
    void validate(const std::string& fn, func_args args, const std::string& body, const std::string rt) const {
        FunctionBodyValidator validator(fn, args, body, rt);
        validator.validate();
    }
};
#endif /* FUNCTION_PARSER_HPP*/