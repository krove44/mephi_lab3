#pragma once
#include <cmath>
#include <optional>
#include "submodule/Sequence/ArraySequence.h"
#include "Structur/Vector.h"
#include <numbers>


constexpr double G = 9.81;
constexpr double Dif = 1e-6;
constexpr double PI = std::numbers::pi;


struct TrajectoryResult {
    double v0;
    double angle;
    double range;
};

//дальность полёта при заданных v0 и угле
double computeRange(double v0, double angle) {
    return (v0 * v0 * std::sin(2.0 * angle)) / G;
}

std::optional<double> findAngle(double v0, double x1, double x2) {
    double lo = 0.0;
    double hi = PI / 4.0;
    double range_lo = 0;
    double range_hi = computeRange(v0, hi);

    if (range_hi < x1) {
        return std::nullopt;
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

    //проверяем финальное значение
    double mid = (lo + hi) / 2.0;
    double r = computeRange(v0, mid);
    if (r >= x1 && r <= x2) {
        return mid;
    }

    return std::nullopt;
}

std::optional<TrajectoryResult> solve(double x1, double x2, double v0_min, double v0_max, double v0_step) {
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
    return std::nullopt;
}

//минимальная v0 для попадания в точку x
double minV0ForRange(double x) {
    return std::sqrt(x * G);
}