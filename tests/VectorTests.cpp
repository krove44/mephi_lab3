#include <gtest/gtest.h>
#include <span>
#include "../vector.h"

TEST(Vector, DefaultConstructor) {
    Vector<int> vec;
    EXPECT_EQ(vec.size(), 0);
}


