#include <iostream>
#include "Structur/FuncList.h"

int main() {
    FuncList<int> sp;
    FuncList<int> sp1 = sp.prepend(10);
    sp = sp.prepend(11);
    std::cout << sp << std::endl;
    std::cout << sp1;
    return 0;
}