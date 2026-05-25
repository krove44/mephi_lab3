#include "TrajectoryCalculation.h"
#include "Structur/Vector.h"
//TODO: слишком умная функция разбить на несколько, подумать про namespace в матрице
Vec2d rotation(double angle, Vec2d vec)  {
    double cos = std::cos(angle);
    double sin = std::sin(angle);
    Matrix<ArraySequence, double, 2> rotate_matrix = {{{cos, -sin}, {sin, cos}}};
    return rotate_matrix*vec;
    }


double computeRange(double v0, double angle) {
    return (v0 * v0 * std::sin(2.0 * angle)) / G;
}

Optional<double> findAngle(double v0, Vec2d vec) {
    double lo = 0.0;
    double hi = PI / 4.0;
    double range_lo = 0;
    double range_hi = computeRange(v0, hi);

    if (range_hi < vec[0]) {
        return Optional<double>();
    }

    if (range_hi <= vec[1]) {
        return hi;
    }

    while (hi - lo > Dif) {
        double mid = (lo + hi) / 2.0;
        double r = computeRange(v0, mid);

        if (r < vec[0]) {
            lo = mid;
        } 
        else if (r > vec[1]) {
            hi = mid;
        } 
        else {
            return mid;
        }
    }
    
    double mid = (lo + hi) / 2.0;
    double r = computeRange(v0, mid);
    if (r >= vec[0] && r <= vec[1]) {
        return mid;
    }

    return Optional<double>();
}

Optional<TrajectoryResult> solve(Vec2d vec, Vec2d speed, double v0_step) {
    for (double v0 = vec[0]; v0 <= vec[1]; v0 += v0_step) {
        auto angle = findAngle(v0, vec);
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
    Vec2d pos{0.0,0.0};
    Vec2d gravity{0.0,-G};
    for (;pos[1] >= 0.0;) {
        trajectory.Append(pos);
        pos += vec * dt;
        vec += gravity * dt;
    }
    return trajectory;
}