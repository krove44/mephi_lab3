#include <gtest/gtest.h>
#include "../Structur/Matrix.h"
#include "../submodule/Sequence/ArraySequence.h"
#include "../submodule/Sequence/ListSequence.h"

TEST(Matrix, ConstructorArraySequence) {
    Matrix<ListSequence, int, 3> matrix = {{0, 0}, {0, 0}};
    EXPECT_EQ(matrix[0][0], 0);
}

TEST(Matrix, Scalar) {
    Matrix<ListSequence, int, 3> matrix = {{1, 2, 3}, {3, 4, 3}, {0, 1, 3}};
    Matrix<ListSequence, int, 3> new_matrix = matrix*3;
    EXPECT_EQ(new_matrix[0][0], 3);
}