#pragma once
#include <numbers>
#include "submodule/Sequence/ArraySequence.h"
#include "submodule/Sequence/ListSequence.h"
#include "Structur/Vector.h"
#include "Optional.h"
#include "Structur/Matrix.h"

constexpr double G = 9.81;
constexpr double Dif = 1e-6;
constexpr double PI = std::numbers::pi;

using Vec2d = Vec<ArraySequence, double, 2>;

struct TrajectoryResult {
    double v0;
    double angle;
    double range;
};

double computeRange(double v0, double angle);

Optional<double> findAngle(double v0, double x1, double x2);

Optional<TrajectoryResult> solve(double x1, double x2, double v0_min, double v0_max, double v0_step);

double minV0ForRange(double x);

ListSequence<Vec2d> generateTrajectory(double v0, double angle, double dt = 0.01);