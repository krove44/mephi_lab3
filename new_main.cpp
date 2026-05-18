#include <SFML/Graphics.hpp>
#include <string>
#include "submodule/Sequence/ArraySequence.h"
#include <iomanip>
#include "TrajectoryCalculation.h"
//Основное окно
static constexpr float WIN_W   = 1280.f;
static constexpr float WIN_H   =  720.f;
static constexpr float PANEL_W =  260.f;
static constexpr float PAD     =   16.f;
//панелька с параметрами
static constexpr float CX = PANEL_W + 10.f;
static constexpr float CY =  10.f;
static constexpr float CW = WIN_W - CX - 10.f;
static constexpr float CH = WIN_H - CY - 10.f;
//цвета
static const sf::Color BG       {24,  24,  28 };
static const sf::Color PANEL_BG {32,  32,  38 };
static const sf::Color BORDER   {60,  60,  72 };
static const sf::Color TEXT_PRI {220, 220, 225};
static const sf::Color TEXT_SEC {130, 130, 145};
static const sf::Color ACCENT   {29,  158, 117};
static const sf::Color TRY_COL  {110, 110, 125, 110};

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
    float yMax = 80.f;
 
    sf::Vector2f toScreen(float wx, float wy) const {
        float px = CX + (wx / xMax) * CW;
        float py = CY + CH - (wy / yMax) * (CH - 20.f);
        return {px, py};
    }
};

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({static_cast<unsigned int>(WIN_W), static_cast<unsigned int>(WIN_H)}),
        "Trajectory Gui",
        sf::Style::Titlebar | sf::Style::Close
    );
    window.setFramerateLimit(60);
    
    sf::Clock clock;
    float animT = 0.f;
    sf::Font font;
    auto check = font.openFromFile("C:/Windows/Fonts/segoeui.ttf");


    auto drawText = [&](const std::string& str, float x, float y, unsigned size = 14, sf::Color color = TEXT_PRI) {
        sf::Text t(font, str, size);
        t.setFillColor(color);
        t.setPosition({x, y});
        window.draw(t);
    };


    auto drawRect = [&](float x, float y, float w, float h, sf::Color fill, sf::Color outline = sf::Color::Transparent, float thickness = 0.f){
        sf::RectangleShape r({w, h});
        r.setPosition({x, y});
        r.setFillColor(fill);
        if (thickness > 0.f) {
            r.setOutlineColor(outline);
            r.setOutlineThickness(thickness);
        }
        window.draw(r);
    };

    auto drawField = [&](const Field& f) {
        drawRect(f.x, f.y, f.w, 30.f, {40,40,50}, f.active ? ACCENT : BORDER, 1.f);
        drawText(f.label, f.x + 2.f, f.y - 26.f, 20, TEXT_SEC);
        drawText(f.value + (f.active ? "|" : ""), f.x + 8.f, f.y + 7.f, 16);
    };

    auto drawButton = [&](const Button& b, sf::Color fill = ACCENT) {
        drawRect(b.x, b.y, b.w, b.h, fill);
 
        sf::Text t(font, b.label, 14);
        t.setFillColor(sf::Color::White);
        auto tb = t.getLocalBounds();
        t.setPosition({
            b.x + (b.w - tb.size.x) / 2.f - tb.position.x,
            b.y + (b.h - tb.size.y) / 2.f - tb.position.y
        });
        window.draw(t);
    };
 
    auto btnContains = [](const Button& b, sf::Vector2f mp) {
        return sf::FloatRect{{b.x, b.y}, {b.w, b.h}}.contains(mp);
    };

    auto drawTrajectory = [&](const ListSequence<Vec2d>& traj, const CoordMapper& cm, sf::Color color) {
        int n = traj.GetLenght();
        if (n < 2) return;
        sf::VertexArray va(sf::PrimitiveType::LineStrip, n);
        for (int i = 0; i < n; ++i) {
            auto p = traj.Get(i);
            va[i].position = cm.toScreen((float)p[0], (float)p[1]);
            va[i].color    = color;
        }
        window.draw(va);
    };

    float fw = PANEL_W - PAD * 2;
    float fy = 65.f;
    Button calcBtn{"Calculate", PAD, fy + 360, fw, 36.f};

    auto makeField = [&](const char* label, const char* def) {
        Field f{label, def, PAD, fy, fw};
        fy += 60.f;
        return f;
    };

    ArraySequence<Field> fields = {
        makeField("x1 (m):",        "50"),
        makeField("x2 (m):",        "60"),
        makeField("v0 min (m/s):",  "10"),
        makeField("v0 max (m/s):",  "100"),
        makeField("v0 step (m/s):", "5"),
        makeField("dt (s):",        "0.01"),
    };
    int activeField = -1;
    bool btnPressed = false;
    std::string statusMsg = "";
    sf::Color   statusColor = TEXT_SEC;

    CoordMapper cm;
    ArraySequence<ListSequence<Vec2d>> tries;
    ListSequence<Vec2d> solution;
    bool hasSolution = false;
    TrajectoryResult result{};

    auto runCalc = [&]() {
        tries.Clear();
        hasSolution = false;
        try {
            double x1    = std::stod(fields[0].value);
            double x2    = std::stod(fields[1].value);
            double vmin  = std::stod(fields[2].value);
            double vmax  = std::stod(fields[3].value);
            double vstep = std::stod(fields[4].value);
            double dt    = std::stod(fields[5].value);
 
            if (x1 >= x2 || vmin >= vmax || vstep <= 0 || dt <= 0) {
                statusMsg   = "Error: check parameters";
                statusColor = sf::Color{220, 80, 80};
                return;
            }

            for (double v0 = vmin; v0 <= vmax; v0 += vstep) {
                auto ang = findAngle(v0, x1, x2);
                double a = ang.has_value() ? ang.value() : PI / 4.0;
                tries.Append(generateTrajectory(v0, a, dt));
 
                if (ang.has_value()) {
                    hasSolution = true;
                    result = {v0, a, computeRange(v0, a)};
                    solution = tries.GetLast();
 
                    double maxY = 0;
                    for (int i = 0; i < solution.GetLenght(); ++i)
                        maxY = std::max(maxY, solution.Get(i)[1]);
                    cm.xMax = (float)(result.range * 1.15f);
                    cm.yMax = (float)(maxY > 0 ? maxY * 1.2 : 80);
 
                    std::ostringstream ss;
                    ss << std::fixed << std::setprecision(2);
                    ss << "v0=" << result.v0 << " m/s  "
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
 
        } catch (...) {
            statusMsg   = "Error: invalid input";
            statusColor = sf::Color{220, 80, 80};
        }
    };

    while (window.isOpen())
    {   
        btnPressed = false;
        float dt_frame = clock.restart().asSeconds();
        if (hasSolution) {
            animT += dt_frame * 0.4f;
            if (animT > 1.f) animT = 0.f;
        }
        while (const auto ev = window.pollEvent())
        {
            
            if (ev->is<sf::Event::Closed>()) window.close();
 
            if (const auto* mb = ev->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2f mp((float)mb->position.x, (float)mb->position.y);
                activeField = -1;
                for (int i = 0; i < (int)fields.GetLenght(); ++i) {
                    sf::FloatRect rect{{fields[i].x, fields[i].y}, {fields[i].w, 30.f}};
                    fields[i].active = rect.contains(mp);
                    if (fields[i].active) activeField = i;
                }
                if (btnContains(calcBtn, mp)) {
                    btnPressed = true;
                    runCalc();
                }
            }

            

            if (const auto* kt = ev->getIf<sf::Event::KeyPressed>()) {
                if (kt->code == sf::Keyboard::Key::Backspace
                    && activeField >= 0
                    && !fields[activeField].value.empty())
                    fields[activeField].value.pop_back();
                if (kt->code == sf::Keyboard::Key::Tab && activeField >= 0) {
                    fields[activeField].active = false;
                    activeField = (activeField + 1) % (int)fields.GetLenght();
                    fields[activeField].active = true;
                }
                if (kt->code == sf::Keyboard::Key::Enter) {
                    btnPressed = true;
                    runCalc();
                }
            }

            if (const auto* mb = ev->getIf<sf::Event::MouseButtonReleased>()) {
                btnPressed = false;
            }
 
            if (const auto* tc = ev->getIf<sf::Event::TextEntered>()) {
                if (activeField >= 0) {
                    char c = (char)tc->unicode;
                    if ((c >= '0' && c <= '9') || c == '.' || c == '-')
                        fields[activeField].value += c;
                }
            }
        }
        window.clear(BG);

        drawRect(0, 0, PANEL_W, WIN_H, PANEL_BG);
        drawText("Parameters:", PAD, 16.f, 20, TEXT_SEC);

        for (auto& f : fields) drawField(f);
        drawButton(calcBtn, btnPressed ? sf::Color{20, 110, 82} : ACCENT);
    
        drawRect(CX, CY, CW, CH, {28, 28, 34}, BORDER, 1.f);

        sf::Vertex axX[] = {
    sf::Vertex(cm.toScreen(0, 0),       sf::Color{70, 70, 85}),
    sf::Vertex(cm.toScreen(cm.xMax, 0), sf::Color{70, 70, 85})};
        window.draw(axX, 2, sf::PrimitiveType::Lines);

        float step = cm.xMax / 6.f;
        for (float v = 0; v <= cm.xMax + 0.1f; v += step) {
            auto sp = cm.toScreen(v, 0);

            sf::Vertex tick[] = {
        sf::Vertex(sf::Vector2f{sp.x, sp.y+10 - 3.f}, sf::Color{70, 70, 85}),
        sf::Vertex(sf::Vector2f{sp.x, sp.y+10 + 3.f}, sf::Color{70, 70, 85})};
            window.draw(tick, 2, sf::PrimitiveType::Lines);

            std::ostringstream ss;
            ss << (int)v << "m";
            drawText(ss.str(), sp.x - 10.f, sp.y - 15.f, 15, sf::Color{130, 130, 145});
        }

        for (auto& t : tries) drawTrajectory(t, cm, TRY_COL);

        if (hasSolution) {
            drawTrajectory(solution, cm, ACCENT);
            auto fmt = [](double v, int p = 2) {
                std::ostringstream s;
                s << std::fixed << std::setprecision(p) << v;
                return s.str();
            };
            float ry = calcBtn.y + 50.f;
            drawText("v0    = " + fmt(result.v0)                + " m/s", PAD, ry,        18, statusColor);
            drawText("angle = " + fmt(result.angle*180.0/PI, 1) + " deg", PAD, ry + 18.f, 18, statusColor);
            drawText("range = " + fmt(result.range, 1)          + " m",   PAD, ry + 36.f, 18, statusColor);
            int n   = solution.GetLenght();
            int idx = std::min((int)(animT * n), n - 1);

            auto pt = solution.Get(idx);
            auto sp = cm.toScreen((float)pt[0], (float)pt[1]);

            sf::CircleShape ball(6.f);
            ball.setOrigin({6.f, 6.f});
            ball.setPosition(sp);
            ball.setFillColor(ACCENT);
            window.draw(ball);
        }
        window.display();
    }

    return 0;
}