// #ifndef INTERPRETER_H
// #define INTERPRETER_H

// #include "core.h"


// #include <map>
// #include <vector>
// #include <string>
// #include <sstream>
// #include <fstream>
// #include <memory>
// #include <stdexcept>
// #include <algorithm>

// class Interpreter {
// private:
//     // std::map<std::string, std::shared_ptr<MathObject>> variables;

//     template<AllowedTypes T>
//     std::vector<T> parseVectorElements(const std::string& str) {
//         std::vector<T> elements;
//         std::string temp = str;
        
//         // Remove brackets
//         temp = temp.substr(1, temp.length() - 2);
        
//         std::istringstream iss(temp);
//         int value;
//         while (iss >> value) {
//             elements.push_back(Rational(value));
//         }
        
//         return elements;
//     }

// public:
//     void executeCommand(const std::string& line) {
//         try {
//             std::istringstream iss(line);
//             std::string varName;
//             std::string equals;
//             std::string value;

//             iss >> varName;
//             if (varName.empty()) return;

//             // Check if this is an assignment
//             if (iss >> equals) {
//                 if (equals != "=") {
//                     throw std::runtime_error("Expected '=' after variable name");
//                 }

//                 // Get the rest of the line for the value
//                 std::getline(iss, value);
//                 // Remove leading whitespace
//                 value.erase(0, value.find_first_not_of(" \t"));

//                 if (value.front() == '[' && value.back() == ']') {
//                     auto elements = parseVectorElements(value);
//                     variables[varName] = std::make_shared<Vector>(elements);
//                 } else {
//                     throw std::runtime_error("Unsupported value type");
//                 }
//             } else {
//                 // Variable lookup
//                 auto it = variables.find(varName);
//                 if (it != variables.end()) {
//                     std::cout << it->second->toString() << std::endl;
//                 } else {
//                     throw std::runtime_error("Variable not found: " + varName);
//                 }
//             }
//         } catch (const std::exception& e) {
//             std::cerr << "Error: " << e.what() << std::endl;
//         }
//     }
// };
// #endif /* INTERPRETER_H */