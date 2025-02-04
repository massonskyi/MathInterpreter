// #ifndef AST_OPTIMIZER_H
// #define AST_OPTIMIZER_H

// #include "ast.h"
// #include <memory>

// class ASTOptimizer
// {
// public:
//     static std::shared_ptr<ASTNode> optimize(const std::shared_ptr<ASTNode> &node)
//     {
//         return optimize_node(node);
//     }

// private:
//     static std::shared_ptr<ASTNode> optimize_node(const std::shared_ptr<ASTNode> &node)
//     {
//         if (auto number_node = dynamic_cast<NumberNode *>(node.get()))
//         {
//             return std::make_unique<NumberNode>(number_node->evaluate());
//         }
//         else if (auto binary_op_node = dynamic_cast<BinaryOpNode *>(node.get()))
//         {
//             auto left_optimized = optimize_node(binary_op_node->Left());
//             auto right_optimized = optimize_node(binary_op_node->Right());

//             if (auto left_num = dynamic_cast<NumberNode *>(left_optimized.get());
//                 left_num && dynamic_cast<NumberNode *>(right_optimized.get()))
//             {
//                 if (auto right_num = dynamic_cast<NumberNode *>(right_optimized.get());
//                     right_num)
//                 {
//                     // auto oper = binary_op_node->Op();
//                     // auto result = std::visit([&oper](auto &&left, auto &&right) -> Variable
//                     //         { 
//                     //             using L = std::decay_t<decltype(left)>;
//                     //             using R = std::decay_t<decltype(right)>,;
                                
//                     //             if(std::is_same_v<L, Variable> || std::is_same_v<R, Variable>)
//                     //                 return apply_operation(std::get<Variable>(left), std::get<Variable>(right), oper);
//                     //         }, left_num->evaluate(), right_num->evaluate());

//                     // return std::make_unique<NumberNode>(result);
//                     throw std::runtime_error("Not implemented");
//                 }
//             }

//             return std::make_unique<BinaryOpNode>(binary_op_node->Op(), std::move(left_optimized), std::move(right_optimized));
//         }
//         else if (auto variable_node = dynamic_cast<VariableNode *>(node.get()))
//         {
//             return std::make_unique<VariableNode>(variable_node->evaluate(), variable_node->pos());
//         }
//         else if (auto function_call_node = dynamic_cast<FunctionCallNode *>(node.get()))
//         {
//             std::vector<std::shared_ptr<ASTNode>> optimized_args;
//             for (const auto &arg : function_call_node->Args())
//             {
//                 optimized_args.push_back(optimize_node(arg));
//             }
//             return std::make_unique<FunctionCallNode>(function_call_node->Name(), std::move(optimized_args));
//         }

//         throw std::runtime_error("Unknown AST node type");
//     }

//     static Variable apply_operation(Variable &lhs, Variable &rhs, const std::string &op)
//     {
//         if (op == "+")
//             return lhs + rhs;
//         if (op == "-")
//             return lhs - rhs;
//         if (op == "*")
//             return lhs * rhs;
//         if (op == "/")
//         {
//             if (rhs == 0)
//                 throw std::runtime_error("Division by zero");
//             return lhs / rhs;
//         }
//         throw std::runtime_error("Unsupported operation: " + op);
//     }
// };

// #endif // AST_OPTIMIZER_H