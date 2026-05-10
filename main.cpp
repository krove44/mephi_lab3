#include <iostream>
#include "vector.h"
#include "span"

int main() {
    int data[] = {1, 2, 3};
    Vector<int> sp(std::span(data, 3));
    Vector<int> sp1(std::span(data, 3));
    Vector<int> sum = sp + sp1;
    for (auto& i : sum){
        std::cout << i << " ";
    }
    return 0;
}