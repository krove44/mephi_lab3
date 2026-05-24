#include <SFML/Graphics.hpp>
#include <string>
#include <iomanip>
#include "Model.h"
#include <fstream>
#include "RightPanel.h"
int main()
{
    sf::RenderWindow window(
        sf::VideoMode({static_cast<unsigned int>(WIN_W), static_cast<unsigned int>(WIN_H)}),
        "Trajectory Gui"
    );
    window.setFramerateLimit(60);

    sf::Clock clock;
    sf::Font font;
    font.openFromFile("C:/Windows/Fonts/segoeui.ttf");
    Model model;
    RightPanel panel(window, font);
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

    while (window.isOpen()) {
        model.btnPressed = false;
        float dt_frame = clock.restart().asSeconds();
        model.update(dt_frame);
 
        while (const auto ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) window.close();

            if (const auto* mb = ev->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2f mp((float)mb->position.x, (float)mb->position.y);
                model.activeField = -1;
                for (int i = 0; i < (int)model.fields.GetLenght(); ++i) {
                    sf::FloatRect rect{{model.fields[i].x, model.fields[i].y}, {model.fields[i].w, 30.f}};
                    model.fields[i].active = rect.contains(mp);
                    if (model.fields[i].active) model.activeField = i;
                }
                if (btnContains(model.calcBtn, mp)) {
                    model.btnPressed = true;
                    model.runCalc();
                }
            }
 
            if (const auto* kt = ev->getIf<sf::Event::KeyPressed>()) {
                if (kt->code == sf::Keyboard::Key::Backspace
                    && model.activeField >= 0
                    && !model.fields[model.activeField].value.empty())
                    model.fields[model.activeField].value.pop_back();
                if (kt->code == sf::Keyboard::Key::Tab && model.activeField >= 0) {
                    model.fields[model.activeField].active = false;
                    model.activeField = (model.activeField + 1) % (int)model.fields.GetLenght();
                    model.fields[model.activeField].active = true;
                }
                if (kt->code == sf::Keyboard::Key::Enter) {
                    model.btnPressed = true;
                    model.runCalc();
                }
            }

            if (const auto* mb = ev->getIf<sf::Event::MouseButtonReleased>()) {
                model.btnPressed = false;
            }
 
            if (const auto* tc = ev->getIf<sf::Event::TextEntered>()) {
                if (model.activeField >= 0) {
                    char c = (char)tc->unicode;
                    if ((c >= '0' && c <= '9') || c == '.' || c == '-')
                        model.fields[model.activeField].value += c;
                }
            }
        }

        window.clear(BG);
        panel.drawPanel(model);
        panel.drawRect({CX, CY}, {CW, CH}, {28, 28, 34}, BORDER, 1.f);

        sf::Vertex axX[] = {
            sf::Vertex(model.cm.toScreen(0, 0),            sf::Color{70, 70, 85}),
            sf::Vertex(model.cm.toScreen(model.cm.xMax, 0), sf::Color{70, 70, 85})};
        window.draw(axX, 2, sf::PrimitiveType::Lines);
        float step = model.cm.xMax / 6.f;
        for (float v = 0; v <= model.cm.xMax + 0.1f; v += step) {
            auto sp = model.cm.toScreen(v, 0);
            sf::Vertex tick[] = {
                sf::Vertex(sf::Vector2f{sp.x, sp.y+10 - 3.f}, sf::Color{70, 70, 85}),
                sf::Vertex(sf::Vector2f{sp.x, sp.y+10 + 3.f}, sf::Color{70, 70, 85})};
            window.draw(tick, 2, sf::PrimitiveType::Lines);

            std::ostringstream ss;
            ss << (int)v << "m";
            panel.drawText(ss.str(), {sp.x - 10.f, sp.y - 15.f}, 15, sf::Color{130, 130, 145});
        }

        for (auto& t : model.tries) drawTrajectory(t, model.cm, TRY_COL);

        if (model.hasSolution) {
            drawTrajectory(model.solution, model.cm, ACCENT);

            int n   = model.solution.GetLenght();
            int idx = std::min((int)(model.animT * n), n - 1);
            auto pt = model.solution.Get(idx);
            auto sp = model.cm.toScreen((float)pt[0], (float)pt[1]);

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