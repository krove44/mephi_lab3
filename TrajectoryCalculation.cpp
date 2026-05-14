#include "TrajectoryCalculation.h"

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
    double vx = v0 * std::cos(angle); // ROTATE MATRIX
    double vy = v0 * std::sin(angle);
    double t_flight = 2.0 * vy / G;
    Vec2d pos{0,0}; // TODO: VEC MATH
    
    for (double t = 0.0; t <= t_flight; t += dt) {
        // pos += vel * dt ;
    
        double x = vx * t;
        double y = vy * t - 0.5 * G * t * t;
    
        ArraySequence<double> coords;
        coords.Append(x);
        coords.Append(y);
        trajectory.Append(Vec2d(coords));
    }
    return trajectory;
}