#include <iostream>
#include <span>
#include "Structur/FuncList.h"
#include "Structur/Vector.h"

int main() {
    int data[] = {1, 2, 3};
    int data1[] = {1, 2};
    Vector<int> sp(std::span<int>(data, 3));
    Vector<int> sp1(std::span<int>(data1, 2));
    std::cout << sp.dot(sp1);
    return 0;
}