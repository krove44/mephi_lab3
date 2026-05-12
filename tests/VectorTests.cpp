#include <gtest/gtest.h>
#include <complex>
#include "../Structur/Vector.h"
#include "../submodule/Sequence/ArraySequence.h"
#include "../submodule/Sequence/ListSequence.h"

TEST(Vec, SizeConstructorArraySequence) {
    Vec<ArraySequence, int> vec(5);
    EXPECT_EQ(vec.GetLenght(), 0);
}

TEST(Vec, CopyConstructorArraySequence) {
    int arr[] = {1, 2, 3};
    Vec<ArraySequence, int> vec(std::span<int>(arr, 3));
    Vec<ArraySequence, int> copy(vec);
    EXPECT_EQ(copy.GetLenght(), 3);
    EXPECT_EQ(copy[0], 1);
}

TEST(Vec, CopyConstructorListSequence) {
    int arr[] = {1, 2, 3};
    Vec<ListSequence, int> vec(std::span<int>(arr, 3));
    Vec<ListSequence, int> copy(vec);
    EXPECT_EQ(copy.GetLenght(), 3);
    EXPECT_EQ(copy[0], 1);
}

TEST(Vec, AdditionIntArraySequence) {
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    Vec<ArraySequence, int> va(std::span<int>(a, 3));
    Vec<ArraySequence, int> vb(std::span<int>(b, 3));
    Vec<ArraySequence, int> result = va + vb;
    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 7);
    EXPECT_EQ(result[2], 9);
}

TEST(Vec, AdditionIntListSequence) {
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    Vec<ListSequence, int> va(std::span<int>(a, 3));
    Vec<ListSequence, int> vb(std::span<int>(b, 3));
    Vec<ListSequence, int> result = va + vb;
    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 7);
    EXPECT_EQ(result[2], 9);
}

TEST(Vec, AdditionSizeMismatchArraySequence) {
    int a[] = {1, 2, 3};
    int b[] = {1, 2};
    Vec<ArraySequence, int> va(std::span<int>(a, 3));
    Vec<ArraySequence, int> vb(std::span<int>(b, 2));
    EXPECT_THROW(va + vb, SizeMismatchException);
}

TEST(Vec, AdditionSizeMismatchListSequence) {
    int a[] = {1, 2, 3};
    int b[] = {1, 2};
    Vec<ListSequence, int> va(std::span<int>(a, 3));
    Vec<ListSequence, int> vb(std::span<int>(b, 2));
    EXPECT_THROW(va + vb, SizeMismatchException);
}

TEST(Vec, ScalarMultiplicationArraySequence) {
    int a[] = {1, 2, 3};
    Vec<ArraySequence, int> va(std::span<int>(a, 3));
    Vec<ArraySequence, int> result = va * 3;
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 6);
    EXPECT_EQ(result[2], 9);
}

TEST(Vec, ScalarMultiplicationListSequence) {
    int a[] = {1, 2, 3};
    Vec<ListSequence, int> va(std::span<int>(a, 3));
    Vec<ListSequence, int> result = va * 3;
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 6);
    EXPECT_EQ(result[2], 9);
}

TEST(Vec, NormArraySequence) {
    int a[] = {3, 4};
    Vec<ArraySequence, int> va(std::span<int>(a, 2));
    EXPECT_DOUBLE_EQ(va.norm(), 5.0);
}

TEST(Vec, NormListSequence) {
    int a[] = {3, 4};
    Vec<ListSequence, int> va(std::span<int>(a, 2));
    EXPECT_DOUBLE_EQ(va.norm(), 5.0);
}

TEST(Vec, NormComplexArraySequence) {
    std::complex<double> a[] = {{3.0, 4.0}};
    Vec<ArraySequence, std::complex<double>> va(std::span<std::complex<double>>(a, 1));
    EXPECT_DOUBLE_EQ(va.norm(), 5.0);
}

TEST(Vec, NormComplexListSequence) {
    std::complex<double> a[] = {{3.0, 4.0}};
    Vec<ListSequence, std::complex<double>> va(std::span<std::complex<double>>(a, 1));
    EXPECT_DOUBLE_EQ(va.norm(), 5.0);
}

TEST(Vec, DotProductArraySequence) {
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    Vec<ArraySequence, int> va(std::span<int>(a, 3));
    Vec<ArraySequence, int> vb(std::span<int>(b, 3));
    EXPECT_EQ(va.dot(vb), 32);
}

TEST(Vec, DotProductListSequence) {
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    Vec<ListSequence, int> va(std::span<int>(a, 3));
    Vec<ListSequence, int> vb(std::span<int>(b, 3));
    EXPECT_EQ(va.dot(vb), 32);
}

TEST(Vec, DotProductSizeMismatchArraySequence) {
    int a[] = {1, 2, 3};
    int b[] = {1, 2};
    Vec<ArraySequence, int> va(std::span<int>(a, 3));
    Vec<ArraySequence, int> vb(std::span<int>(b, 2));
    EXPECT_THROW(va.dot(vb), SizeMismatchException);
}

TEST(Vec, DotProductSizeMismatchListSequence) {
    int a[] = {1, 2, 3};
    int b[] = {1, 2};
    Vec<ListSequence, int> va(std::span<int>(a, 3));
    Vec<ListSequence, int> vb(std::span<int>(b, 2));
    EXPECT_THROW(va.dot(vb), SizeMismatchException);
}

TEST(Vec, DoubleAdditionArraySequence) {
    double a[] = {1.5, 2.5};
    double b[] = {0.5, 1.5};
    Vec<ArraySequence, double> va(std::span<double>(a, 2));
    Vec<ArraySequence, double> vb(std::span<double>(b, 2));
    Vec<ArraySequence, double> result = va + vb;
    EXPECT_DOUBLE_EQ(result[0], 2.0);
    EXPECT_DOUBLE_EQ(result[1], 4.0);
}

TEST(Vec, DoubleAdditionListSequence) {
    double a[] = {1.5, 2.5};
    double b[] = {0.5, 1.5};
    Vec<ListSequence, double> va(std::span<double>(a, 2));
    Vec<ListSequence, double> vb(std::span<double>(b, 2));
    Vec<ListSequence, double> result = va + vb;
    EXPECT_DOUBLE_EQ(result[0], 2.0);
    EXPECT_DOUBLE_EQ(result[1], 4.0);
}
