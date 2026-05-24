#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "../submodule/Sequence/ArraySequence.h"
#include "../TrajectoryCalculation.h"

//Основное окно
constexpr float WIN_W   = 1280.f;
constexpr float WIN_H   =  720.f;
constexpr float PANEL_W =  260.f;
constexpr float PAD     =   16.f;

//панелька с параметрами
constexpr float CX = PANEL_W + 10.f;
constexpr float CY =  10.f;
constexpr float CW = WIN_W - CX - 10.f;
constexpr float CH = WIN_H - CY - 10.f;

//цвета
const sf::Color BG       {24,  24,  28 };
const sf::Color PANEL_BG {32,  32,  38 };
const sf::Color BORDER   {60,  60,  72 };
const sf::Color TEXT_PRI {220, 220, 225};
const sf::Color TEXT_SEC {130, 130, 145};
const sf::Color ACCENT   {29,  158, 117};
const sf::Color TRY_COL  {110, 110, 125, 110};

struct Field {
    std::string label;
    std::string value;
    float x, y, w;
    bool active = false;
};

struct Button {
    std::string label;
    float x, y, w, h;
};

struct CoordMapper {
    float xMax = 120.f;
    float yMax =  80.f;

    sf::Vector2f toScreen(float wx, float wy) const {
        float px = CX + (wx / xMax) * CW;
        float py = (CY + CH) - (wy / yMax) * CH;
        return {px, py};
    }

};

Field makeField(const char* label, const char* def, float& fy, float fw) {
    Field f{label, def, PAD, fy, fw};
    fy += 60.f;
    return f;
}
//TODO:единицы трансляции
//TODO:как работает компилятор
struct Model {
    ArraySequence<Field> fields;
    Button calcBtn;
    int activeField = -1;
    bool btnPressed  = false;
    CoordMapper cm;
    ArraySequence<ListSequence<Vec2d>> tries;
    ListSequence<Vec2d> solution;
    bool hasSolution = false;
    TrajectoryResult result{};
    float animT = 0.f;  
    std::string statusMsg   = "";
    sf::Color   statusColor = TEXT_SEC;

    Model() {
        float fw = PANEL_W - PAD * 2;
        float fy = 65.f;
        fields = {
            makeField("x1 (m):", "50", fy, fw),
            makeField("x2 (m):", "60", fy, fw),
            makeField("v0 min (m/s):", "10", fy, fw),
            makeField("v0 max (m/s):", "100", fy, fw),
            makeField("v0 step (m/s):", "5", fy, fw),
            makeField("dt (s):", "0.01", fy, fw),
        };
        calcBtn = {"Calculate", PAD, fy + 50.f, fw, 36.f};
    }

    void runCalc() {
        tries.Clear();
        hasSolution = false;
            double x1    = std::stod(fields[0].value);
            double x2    = std::stod(fields[1].value);
            double vmin  = std::stod(fields[2].value);
            double vmax  = std::stod(fields[3].value);
            double vstep = std::stod(fields[4].value);
            double dt    = std::stod(fields[5].value);

            if (x1 >= x2 || vmin >= vmax || vstep <= 0 || dt <= 0) {
                statusMsg   = "Error: check parameters";
                //TODO: отдельный класс под view
                statusColor = sf::Color{220, 80, 80};
                return;
            }

            for (double v0 = vmin; v0 <= vmax; v0 += vstep) {
                auto ang = findAngle(v0, {x1, x2});
                double a = ang.has_value() ? ang.value() : PI / 4.0;
                tries.Append(generateTrajectory(v0, a, dt));

                if (ang.has_value()) {
                    hasSolution = true;
                    result      = {v0, a, computeRange(v0, a)};
                    solution    = tries.GetLast();
                    animT       = 0.f;

                    double maxY = 0;
                    for (int i = 0; i < solution.GetLenght(); ++i)
                    maxY = std::max(maxY, solution.Get(i)[1]);
                    cm.xMax = (float)(result.range * 1.15f);
                    cm.yMax = (float)(maxY > 0 ? maxY * 1.2 : 80);

                    std::ostringstream ss;
                    ss << std::fixed << std::setprecision(2)
                       << "v0=" << result.v0 << " m/s  "
                       << "angle=" << result.angle * 180.0 / PI << " deg  "
                       << "range=" << result.range << " m";
                    statusMsg   = ss.str();
                    statusColor = ACCENT;
                    break;
                }
            }

            if (!hasSolution) {
                statusMsg   = "No solution found";
                statusColor = sf::Color{220, 80, 80};
            }

    }

    void update(float t) {
        if (!hasSolution) {
            return;
        }
        animT += t * 0.4f;
        if (animT > 1.f) {
            animT = 0.f;
        }
    }
};