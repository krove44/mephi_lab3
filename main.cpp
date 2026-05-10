#include <iostream>
#include "Structur/FuncList.h"

int main() {
    FuncList<int> sp;
    std::cout << sp.head() << std::endl;
    return 0;
}