// #include <iostream>
// #include "include/variable.hpp"
// #include "include/rational.hpp"
// #include "include/vector.hpp"
// #include "include/matrix.hpp"

// int main(int argc, char** argv) {
//     Variable<int> var   (2);

//     Vector<Variable<int>> vec ({var, var, var, var});
//     Matrix<int> mat;
//     mat.append(vec);
//     // mat = var;
//     // for (int i = 0; i < mat.colsCount(); i++) {
//     //     for(int j = 0; j < mat.rowsCount(); j++) {
//     //         mat[i][j] = var;
//     //         std::cout<<mat[i][j]<<std::endl;
//     //     }
//     // }
//     std::cout << mat << std::endl;
//     return 0;
// }