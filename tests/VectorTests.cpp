#include <gtest/gtest.h>
#include <span>
#include <complex>
#include "../Structur/vector.h"

TEST(Vector, DefaultConstructor) {
    Vector<int> vec;
    EXPECT_EQ(vec.size(), 0);
}

TEST(Vector, SizeConstructor) {
    Vector<int> vec(5);
    EXPECT_EQ(vec.size(), 5);
}

TEST(Vector, SpanConstructor) {
    int arr[] = {1, 2, 3};
    Vector<int> vec(std::span<int>(arr, 3));
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(Vector, CopyConstructor) {
    int arr[] = {1, 2, 3};
    Vector<int> vec(std::span<int>(arr, 3));
    Vector<int> copy(vec);
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy[0], 1);
}

TEST(Vector, PushBack) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}

TEST(Vector, AdditionInt) {
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    Vector<int> va(std::span<int>(a, 3));
    Vector<int> vb(std::span<int>(b, 3));
    Vector<int> result = va + vb;
    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 7);
    EXPECT_EQ(result[2], 9);
}

TEST(Vector, AdditionSizeMismatch) {
    int a[] = {1, 2, 3};
    int b[] = {1, 2};
    Vector<int> va(std::span<int>(a, 3));
    Vector<int> vb(std::span<int>(b, 2));
    EXPECT_THROW(va + vb, SizeMismatchException);
}

TEST(Vector, ScalarMultiplication) {
    int a[] = {1, 2, 3};
    Vector<int> va(std::span<int>(a, 3));
    Vector<int> result = va * 3;
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 6);
    EXPECT_EQ(result[2], 9);
}

TEST(Vector, Norm) {
    int a[] = {3, 4};
    Vector<int> va(std::span<int>(a, 2));
    EXPECT_DOUBLE_EQ(va.norm(), 5.0);
}
