#include "TrajectoryCalculation.h"

Vec2d rotation(double angle, Vec2d vec)  {
    double cos = std::cos(angle);
    double sin = std::sin(angle);
    Matrix<ArraySequence, double, 2> rotate_matrix = {{cos, -sin}, {sin, cos}};
    return rotate_matrix*vec;
    }


double computeRange(double v0, double angle) {
    return (v0 * v0 * std::sin(2.0 * angle)) / G;
}

Optional<double> findAngle(double v0, double x1, double x2) {
    double lo = 0.0;
    double hi = PI / 4.0;
    double range_lo = 0;
    double range_hi = computeRange(v0, hi);

    if (range_hi < x1) {
        return Optional<double>();
    }

    if (range_hi <= x2) {
        return hi;
    }

    while (hi - lo > Dif) {
        double mid = (lo + hi) / 2.0;
        double r = computeRange(v0, mid);

        if (r < x1) {
            lo = mid;
        } 
        else if (r > x2) {
            hi = mid;
        } 
        else {
            return mid;
        }
    }
    
    double mid = (lo + hi) / 2.0;
    double r = computeRange(v0, mid);
    if (r >= x1 && r <= x2) {
        return mid;
    }

    return Optional<double>();
}

Optional<TrajectoryResult> solve(double x1, double x2, double v0_min, double v0_max, double v0_step) {
    for (double v0 = v0_min; v0 <= v0_max; v0 += v0_step) {
        auto angle = findAngle(v0, x1, x2);
        if (angle.has_value()) {
            return TrajectoryResult{
                .v0    = v0,
                .angle = angle.value(),
                .range = computeRange(v0, angle.value())
            };
        }
    }
    return Optional<TrajectoryResult>();
}

double minV0ForRange(double x) {
    return std::sqrt(x * G);
}

ListSequence<Vec2d> generateTrajectory(double v0, double angle, double dt) {
    ListSequence<Vec2d> trajectory;
    Vec2d vec = rotation(angle, Vec2d({v0, 0.0}));
    FILE* f = fopen("C:/Users/krove44/Desktop/mephi_lab3/build/debug.txt", "w");
    fprintf(f, "vec length: %d\n", (int)vec.GetLenght());
    if (vec.GetLenght() >= 2) {
        fprintf(f, "vec[0]=%f vec[1]=%f\n", vec[0], vec[1]);
    }
    fclose(f);
    Vec2d pos{0.0,0.0};
    Vec2d gravity{0.0,-G};
    for (;pos[1] >= 0.0;) {
        trajectory.Append(pos);
        vec = vec + gravity*dt;
        pos = pos + vec*dt;
    }
    return trajectory;
}