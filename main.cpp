#include <cstddef>
#include <iostream>
#include "Structur/vector.h"
#include "span"

int main() {
    int data[] = {1, 2, 3};
    Vector<int> sp(std::span(data, 3));
    int res = sp.reduce([](int x, int z){return x + z;}, 10);
    std::cout << res;
    return 0;
}