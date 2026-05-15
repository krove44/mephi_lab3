#include <iostream>
#include "submodule/Sequence/ListSequence.h"
#include "Structur/Matrix.h"

int main() {
    Matrix<ListSequence, int, 3> matrix = {{1, 2, 3}, {3, 4, 3},{1, 2}};
    Matrix<ListSequence, int, 3> new_matrix = matrix*3;
    for(size_t i = 0; i < 3; i++){
        for(size_t j = 0; j < 3; j++){
            std::cout << new_matrix[i][j] << " ";
        }
    }
    return 0;
}