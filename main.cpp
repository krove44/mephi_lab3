#include <iostream>
#include "TrajectoryCalculation.h"


int main() {
    auto result = solve(10.0, 10.0, 70.0, 100.0, 5.0);
    if (result) {
        std::cout << "v0 = " << result->v0 << std::endl;
        std::cout << "angle = " << result->angle * 180.0 / PI << " deg" << std::endl;
        std::cout << "range = " << result->range << " m" << std::endl;
    } 
    else {
        std::cout << "No solution" << std::endl;
    }
    return 0;
}