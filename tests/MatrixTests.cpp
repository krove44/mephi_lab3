#include <gtest/gtest.h>
#include "../Structur/Matrix.h"
#include "../submodule/Sequence/ArraySequence.h"
#include "../submodule/Sequence/ListSequence.h"

TEST(Matrix, ConstructorArraySequence) {
    Matrix<ListSequence, int, 3> matrix = {{0, 0}, {0, 0}};
    EXPECT_EQ(matrix[0][0], 0);
}