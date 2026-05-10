#include <gtest/gtest.h>
#include "../Structur/FuncList.h"

TEST(FuncList, DefaultConstructor) {
    FuncList<int> list;
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
}

TEST(FuncList, Prepend) {
    FuncList<int> list;
    list = list.prepend(1);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.head(), 1);
}

TEST(FuncList, PrependMultiple) {
    FuncList<int> list;
    list = list.prepend(3).prepend(2).prepend(1);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.head(), 1);
    EXPECT_EQ(list.tail().head(), 2);
    EXPECT_EQ(list.tail().tail().head(), 3);
}

TEST(FuncList, PrependDoesNotMutate) {
    FuncList<int> a;
    a = a.prepend(1);
    FuncList<int> b = a.prepend(0);
    EXPECT_EQ(a.size(), 1);
    EXPECT_EQ(a.head(), 1);
    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(b.head(), 0);
}

TEST(FuncList, HeadEmpty) {
    FuncList<int> list;
    EXPECT_THROW(list.head(), FuncListEmpthy);
}

TEST(FuncList, TailEmpty) {
    FuncList<int> list;
    EXPECT_THROW(list.tail(), FuncListEmpthy);
}

TEST(FuncList, Tail) {
    FuncList<int> list;
    list = list.prepend(2).prepend(1);
    FuncList<int> t = list.tail();
    EXPECT_EQ(t.size(), 1);
    EXPECT_EQ(t.head(), 2);
}

TEST(FuncList, Concat) {
    FuncList<int> a;
    a = a.prepend(2).prepend(1);
    FuncList<int> b;
    b = b.prepend(4).prepend(3);
    FuncList<int> result = a.concat(b);
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result.head(), 1);
    EXPECT_EQ(result.tail().head(), 2);
    EXPECT_EQ(result.tail().tail().head(), 3);
    EXPECT_EQ(result.tail().tail().tail().head(), 4);
}

TEST(FuncList, ConcatEmpty) {
    FuncList<int> a;
    a = a.prepend(1);
    FuncList<int> b;
    FuncList<int> result = a.concat(b);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.head(), 1);
}

TEST(FuncList, ConcatWithEmpty) {
    FuncList<int> a;
    FuncList<int> b;
    b = b.prepend(1);
    FuncList<int> result = a.concat(b);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.head(), 1);
}

TEST(FuncList, ConcatDoesNotMutate) {
    FuncList<int> a;
    a = a.prepend(1);
    FuncList<int> b;
    b = b.prepend(2);
    a.concat(b);
    EXPECT_EQ(a.size(), 1);
    EXPECT_EQ(b.size(), 1);
}

TEST(FuncList, Double) {
    FuncList<double> list;
    list = list.prepend(2.5).prepend(1.5);
    EXPECT_DOUBLE_EQ(list.head(), 1.5);
    EXPECT_DOUBLE_EQ(list.tail().head(), 2.5);
}

TEST(FuncList, Map) {
    FuncList<int> list;
    list = list.prepend(3).prepend(2).prepend(1);
    FuncList<int> result = list.map([](int x) { return x * 2; });
    EXPECT_EQ(result.head(), 2);
    EXPECT_EQ(result.tail().head(), 4);
    EXPECT_EQ(result.tail().tail().head(), 6);
}

TEST(FuncList, MapEmpty) {
    FuncList<int> list;
    FuncList<int> result = list.map([](int x) { return x * 2; });
    EXPECT_TRUE(result.empty());
}

TEST(FuncList, MapDoesNotMutate) {
    FuncList<int> list;
    list = list.prepend(1);
    list.map([](int x) { return x * 2; });
    EXPECT_EQ(list.head(), 1);
}

TEST(FuncList, Where) {
    FuncList<int> list;
    list = list.prepend(5).prepend(4).prepend(3).prepend(2).prepend(1);
    FuncList<int> result = list.where([](int x) { return x % 2 == 0; });
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.head(), 2);
    EXPECT_EQ(result.tail().head(), 4);
}

TEST(FuncList, WhereNoneMatch) {
    FuncList<int> list;
    list = list.prepend(3).prepend(1);
    FuncList<int> result = list.where([](int x) { return x % 2 == 0; });
    EXPECT_TRUE(result.empty());
}

TEST(FuncList, WhereAllMatch) {
    FuncList<int> list;
    list = list.prepend(4).prepend(2);
    FuncList<int> result = list.where([](int x) { return x % 2 == 0; });
    EXPECT_EQ(result.size(), 2);
}

TEST(FuncList, WhereEmpty) {
    FuncList<int> list;
    FuncList<int> result = list.where([](int x) { return x % 2 == 0; });
    EXPECT_TRUE(result.empty());
}

TEST(FuncList, WhereDoesNotMutate) {
    FuncList<int> list;
    list = list.prepend(2).prepend(1);
    list.where([](int x) { return x % 2 == 0; });
    EXPECT_EQ(list.size(), 2);
}

TEST(FuncList, ReduceSum) {
    FuncList<int> list;
    list = list.prepend(3).prepend(2).prepend(1);
    int result = list.reduce([](int x, int w) { return x + w; }, 0);
    EXPECT_EQ(result, 6);
}

TEST(FuncList, ReduceWithStart) {
    FuncList<int> list;
    list = list.prepend(3).prepend(2).prepend(1);
    int result = list.reduce([](int x, int w) { return x + w; }, 10);
    EXPECT_EQ(result, 16);
}

TEST(FuncList, ReduceMultiply) {
    FuncList<int> list;
    list = list.prepend(4).prepend(3).prepend(2).prepend(1);
    int result = list.reduce([](int x, int w) { return x * w; }, 1);
    EXPECT_EQ(result, 24);
}

TEST(FuncList, ReduceEmpty) {
    FuncList<int> list;
    int result = list.reduce([](int x, int w) { return x + w; }, 42);
    EXPECT_EQ(result, 42);
}

TEST(FuncList, ReduceDoesNotMutate) {
    FuncList<int> list;
    list = list.prepend(1);
    list.reduce([](int x, int w) { return x + w; }, 0);
    EXPECT_EQ(list.size(), 1);
}