#include <iostream>
#include <span>
#include "submodule/Sequence/ArraySequence.h"
#include "Structur/Vector.h"

int main() {
    int data[] = {1, 2, 3};
    ArraySequence<int> ase(std::span(data, 3));
    Vec<ArraySequence, int> sp(ase);
    Vec<ArraySequence, int> qqq = 3*sp;
    for(size_t i = 0; i < qqq.GetLenght(); i++){
        std::cout << qqq[i] << " ";
    }
    std::cout << std::endl;
    std::cout << sp.norm() << std::endl;
    std::cout << sp.dot(sp) << std::endl;
    return 0;
}