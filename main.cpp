#include <iostream>
#include "Structur/FuncList.h"

int main() {
    FuncList<int> sp;
    sp = sp.prepend(1).prepend(2).prepend(3);
    std::cout << sp.reduce([](int x, int z){return x + z;}, 0) << std::endl;
    return 0;
}