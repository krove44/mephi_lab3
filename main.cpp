#include <iostream>
#include <span>
#include "submodule/Sequence/ArraySequence.h"
#include "Structur/Vector.h"

int main() {
    int data[] = {1, 2, 3};
    ArraySequence<int> ase(std::span(data, 3));
    Vec<ArraySequence, int> sp(ase);
    Vec<ArraySequence, int> qqq = sp + sp;
    for(size_t i = 0; i < qqq.GetLenght(); i++){
        std::cout << qqq[i] << " ";
    }
    return 0;
}