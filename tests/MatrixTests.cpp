#include <gtest/gtest.h>
#include "../Structur/Matrix.h"
#include "../submodule/Sequence/ArraySequence.h"
#include "../submodule/Sequence/ListSequence.h"

TEST(Matrix, ConstructorWrongRows) {
    EXPECT_THROW((Matrix<ArraySequence, int, 3>{{0, 0}, {0, 0}}), std::exception);
}

TEST(Matrix, ConstructorWrongCols) {
    EXPECT_THROW((Matrix<ArraySequence, int, 3>{{1, 2}, {3, 4}, {5, 6}}), std::exception);
}

TEST(Matrix, ConstructorValues) {
    Matrix<ArraySequence, int, 2> m = {{1, 2}, {3, 4}};
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[1][0], 3);
    EXPECT_EQ(m[1][1], 4);
}

TEST(Matrix, ConstructorCopy) {
    Matrix<ArraySequence, int, 2> m = {{1, 2}, {3, 4}};
    Matrix<ArraySequence, int, 2> copy(m);
    EXPECT_EQ(copy[0][0], 1);
    EXPECT_EQ(copy[1][1], 4);
}

TEST(Matrix, ScalarZero) {
    Matrix<ArraySequence, int, 2> m = {{1, 2}, {3, 4}};
    Matrix<ArraySequence, int, 2> result = m * 0;
    EXPECT_EQ(result[0][0], 0);
    EXPECT_EQ(result[1][1], 0);
}

TEST(Matrix, ScalarOne) {
    Matrix<ArraySequence, int, 2> m = {{1, 2}, {3, 4}};
    Matrix<ArraySequence, int, 2> result = m * 1;
    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[1][1], 4);
}

TEST(Matrix, ScalarPositive) {
    Matrix<ListSequence, int, 3> m = {{1, 2, 3}, {3, 4, 3}, {0, 1, 3}};
    Matrix<ListSequence, int, 3> result = m * 3;
    EXPECT_EQ(result[0][0], 3);
    EXPECT_EQ(result[1][1], 12);
    EXPECT_EQ(result[2][2], 9);
}

TEST(Matrix, AddZero) {
    Matrix<ArraySequence, int, 2> m = {{1, 2}, {3, 4}};
    Matrix<ArraySequence, int, 2> zero = {{0, 0}, {0, 0}};
    Matrix<ArraySequence, int, 2> result = m + zero;
    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[1][1], 4);
}

TEST(Matrix, AddPositive) {
    Matrix<ArraySequence, int, 2> a = {{1, 2}, {3, 4}};
    Matrix<ArraySequence, int, 2> b = {{5, 6}, {7, 8}};
    Matrix<ArraySequence, int, 2> result = a + b;
    EXPECT_EQ(result[0][0], 6);
    EXPECT_EQ(result[0][1], 8);
    EXPECT_EQ(result[1][0], 10);
    EXPECT_EQ(result[1][1], 12);
}

TEST(Matrix, MulVecIdentity) {
    Matrix<ArraySequence, double, 2> m = {{1.0, 0.0}, {0.0, 1.0}};
    Vec<ArraySequence, double, 2> v = {3.0, 5.0};
    Vec<ArraySequence, double, 2> result = m * v;
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 5.0);
}

TEST(Matrix, MulVecSimple) {
    Matrix<ArraySequence, double, 2> m = {{2.0, 0.0}, {0.0, 3.0}};
    Vec<ArraySequence, double, 2> v = {4.0, 5.0};
    Vec<ArraySequence, double, 2> result = m * v;
    EXPECT_DOUBLE_EQ(result[0], 8.0);
    EXPECT_DOUBLE_EQ(result[1], 15.0);
}
