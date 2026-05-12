#include <iostream>
#include "TrajectoryCalculation.h"
#include <windows.h>


int main() {
    SetConsoleOutputCP(CP_UTF8);
    auto result = solve(50.0, 60.0, 10.0, 100.0, 5.0);
    if (result) {
        std::cout << "v0 = " << result->v0 << std::endl;
        std::cout << "Угл = " << result->angle * 180.0 / PI << " deg" << std::endl;
        std::cout << "Промежуток = " << result->range << " m" << std::endl;

        auto traj = generateTrajectory(result->v0, result->angle);
        std::cout << "Траектория (" << traj.GetLenght() << " точек):\n";
        for (size_t i = 0; i < traj.GetLenght(); ++i) {
            std::cout << "x = " << traj.Get(i)[0] << " y = " << traj.Get(i)[1] << "\n";
        }
    }
    else {
        std::cout << "No solution" << std::endl;
    }
    return 0;
}