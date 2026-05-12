#include <gtest/gtest.h>
#include <complex>
#include "../Structur/Vector.h"
#include "../submodule/Sequence/ArraySequence.h"
#include "../submodule/Sequence/ListSequence.h"

TEST(Vec, SizeConstructorArraySequence) {
    Vec<ArraySequence, int> vec(5);
    EXPECT_EQ(vec.GetLenght(), 0);
}

// TEST(Vec, CopyConstructor) {
//     int arr[] = {1, 2, 3};
//     Vec<int> vec(std::span<int>(arr, 3));
//     Vec<int> copy(vec);
//     EXPECT_EQ(copy.size(), 3);
//     EXPECT_EQ(copy[0], 1);
// }

// TEST(Vec, PushBack) {
//     Vec<int> vec;
//     vec.push_back(1);
//     vec.push_back(2);
//     EXPECT_EQ(vec.size(), 2);
//     EXPECT_EQ(vec[0], 1);
//     EXPECT_EQ(vec[1], 2);
// }

// TEST(Vec, AdditionInt) {
//     int a[] = {1, 2, 3};
//     int b[] = {4, 5, 6};
//     Vec<int> va(std::span<int>(a, 3));
//     Vec<int> vb(std::span<int>(b, 3));
//     Vec<int> result = va + vb;
//     EXPECT_EQ(result[0], 5);
//     EXPECT_EQ(result[1], 7);
//     EXPECT_EQ(result[2], 9);
// }

// TEST(Vec, AdditionSizeMismatch) {
//     int a[] = {1, 2, 3};
//     int b[] = {1, 2};
//     Vec<int> va(std::span<int>(a, 3));
//     Vec<int> vb(std::span<int>(b, 2));
//     EXPECT_THROW(va + vb, SizeMismatchException);
// }

// TEST(Vec, ScalarMultiplication) {
//     int a[] = {1, 2, 3};
//     Vec<int> va(std::span<int>(a, 3));
//     Vec<int> result = va * 3;
//     EXPECT_EQ(result[0], 3);
//     EXPECT_EQ(result[1], 6);
//     EXPECT_EQ(result[2], 9);
// }

// TEST(Vec, Norm) {
//     int a[] = {3, 4};
//     Vec<int> va(std::span<int>(a, 2));
//     EXPECT_DOUBLE_EQ(va.norm(), 5.0);
// }

// TEST(Vec, NormComplex) {
//     std::complex<double> a[] = {{3.0, 4.0}};
//     Vec<std::complex<double>> va(std::span<std::complex<double>>(a, 1));
//     EXPECT_DOUBLE_EQ(va.norm(), 5.0);
// }

// TEST(Vec, DotProduct) {
//     int a[] = {1, 2, 3};
//     int b[] = {4, 5, 6};
//     Vec<int> va(std::span<int>(a, 3));
//     Vec<int> vb(std::span<int>(b, 3));
//     EXPECT_EQ(va.dot(vb), 32);
// }

// TEST(Vec, DotProductSizeMismatch) {
//     int a[] = {1, 2, 3};
//     int b[] = {1, 2};
//     Vec<int> va(std::span<int>(a, 3));
//     Vec<int> vb(std::span<int>(b, 2));
//     EXPECT_THROW(va.dot(vb), SizeMismatchException);
// }

// TEST(Vec, Equality) {
//     int a[] = {1, 2, 3};
//     Vec<int> va(std::span<int>(a, 3));
//     Vec<int> vb(std::span<int>(a, 3));
//     EXPECT_TRUE(va == vb);
// }

// TEST(Vec, InequalityDifferentValues) {
//     int a[] = {1, 2, 3};
//     int b[] = {1, 2, 4};
//     Vec<int> va(std::span<int>(a, 3));
//     Vec<int> vb(std::span<int>(b, 3));
//     EXPECT_FALSE(va == vb);
// }

// TEST(Vec, InequalityDifferentSizes) {
//     int a[] = {1, 2, 3};
//     int b[] = {1, 2};
//     Vec<int> va(std::span<int>(a, 3));
//     Vec<int> vb(std::span<int>(b, 2));
//     EXPECT_FALSE(va == vb);
// }

// TEST(Vec, SelfEquality) {
//     int a[] = {1, 2, 3};
//     Vec<int> va(std::span<int>(a, 3));
//     EXPECT_TRUE(va == va);
// }

// TEST(Vec, DoubleAddition) {
//     double a[] = {1.5, 2.5};
//     double b[] = {0.5, 1.5};
//     Vec<double> va(std::span<double>(a, 2));
//     Vec<double> vb(std::span<double>(b, 2));
//     Vec<double> result = va + vb;
//     EXPECT_DOUBLE_EQ(result[0], 2.0);
//     EXPECT_DOUBLE_EQ(result[1], 4.0);
// }


// TEST(Vec, Map) {
//     int a[] = {1, 2, 3};
//     Vec<int> va(std::span<int>(a, 3));
//     Vec<int> result = va.map([](int x) { return x * 2; });
//     EXPECT_EQ(result[0], 2);
//     EXPECT_EQ(result[1], 4);
//     EXPECT_EQ(result[2], 6);
// }

// TEST(Vec, MapDouble) {
//     double a[] = {1.0, 2.0, 3.0};
//     Vec<double> va(std::span<double>(a, 3));
//     Vec<double> result = va.map([](double x) { return x * x; });
//     EXPECT_DOUBLE_EQ(result[0], 1.0);
//     EXPECT_DOUBLE_EQ(result[1], 4.0);
//     EXPECT_DOUBLE_EQ(result[2], 9.0);
// }

// TEST(Vec, MapEmpty) {
//     Vec<int> va;
//     Vec<int> result = va.map([](int x) { return x * 2; });
//     EXPECT_EQ(result.size(), 0);
// }

// TEST(Vec, Where) {
//     int a[] = {1, 2, 3, 4, 5};
//     Vec<int> va(std::span<int>(a, 5));
//     Vec<int> result = va.where([](int x) { return x % 2 == 0; });
//     EXPECT_EQ(result.size(), 2);
//     EXPECT_EQ(result[0], 2);
//     EXPECT_EQ(result[1], 4);
// }

// TEST(Vec, WhereNoneMatch) {
//     int a[] = {1, 3, 5};
//     Vec<int> va(std::span<int>(a, 3));
//     Vec<int> result = va.where([](int x) { return x % 2 == 0; });
//     EXPECT_EQ(result.size(), 0);
// }

// TEST(Vec, WhereAllMatch) {
//     int a[] = {2, 4, 6};
//     Vec<int> va(std::span<int>(a, 3));
//     Vec<int> result = va.where([](int x) { return x % 2 == 0; });
//     EXPECT_EQ(result.size(), 3);
// }

// TEST(Vec, WhereEmpty) {
//     Vec<int> va;
//     Vec<int> result = va.where([](int x) { return x % 2 == 0; });
//     EXPECT_EQ(result.size(), 0);
// }

// TEST(Vec, Reduce) {
//     int a[] = {1, 2, 3};
//     Vec<int> va(std::span<int>(a, 3));
//     int result = va.reduce([](int x, int w) { return x + w; }, 0);
//     EXPECT_EQ(result, 6);
// }

// TEST(Vec, ReduceWithStart) {
//     int a[] = {1, 2, 3};
//     Vec<int> va(std::span<int>(a, 3));
//     int result = va.reduce([](int x, int w) { return x + w; }, 10);
//     EXPECT_EQ(result, 16);
// }

// TEST(Vec, ReduceMultiply) {
//     int a[] = {1, 2, 3, 4};
//     Vec<int> va(std::span<int>(a, 4));
//     int result = va.reduce([](int x, int w) { return x * w; }, 1);
//     EXPECT_EQ(result, 24);
// }

// TEST(Vec, ReduceEmpty) {
//     Vec<int> va;
//     int result = va.reduce([](int x, int w) { return x + w; }, 42);
//     EXPECT_EQ(result, 42);
// }