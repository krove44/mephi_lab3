#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Model.h"
#include "RightPanel.h"

struct LeftPanel {
    sf::RenderWindow& window;
    RightPanel& panel;

    LeftPanel(sf::RenderWindow& w, RightPanel& p) : window(w), panel(p) {}

    void drawTrajectory(const ListSequence<Vec2d>& traj, const CoordMapper& cm, sf::Color color) {
        int n = traj.GetLenght();
        if (n < 2) return;
        sf::VertexArray va(sf::PrimitiveType::LineStrip, n);
        for (int i = 0; i < n; ++i) {
            auto p = traj.Get(i);
            va[i].position = cm.toScreen((float)p[0], (float)p[1]);
            va[i].color    = color;
        }
        window.draw(va);
    }

    void drawAxes(const CoordMapper& cm) {
        sf::Vertex axX[] = {
            sf::Vertex(cm.toScreen(0, 0), sf::Color{70, 70, 85}),
            sf::Vertex(cm.toScreen(cm.xMax, 0), sf::Color{70, 70, 85})
        };
        window.draw(axX, 2, sf::PrimitiveType::Lines);

        float step = cm.xMax / 6.f;
        for (float v = 0; v <= cm.xMax + 0.1f; v += step) {
            auto sp = cm.toScreen(v, 0);
            Vec2f tickTop = {sp.x, sp.y + 10 - 3.f};
            Vec2f tickBot = {sp.x, sp.y + 10 + 3.f};
            sf::Vertex tick[] = {
                sf::Vertex(sf::Vector2f{tickTop[0], tickTop[1]}, sf::Color{70, 70, 85}),
                sf::Vertex(sf::Vector2f{tickBot[0], tickBot[1]}, sf::Color{70, 70, 85})
            };
            window.draw(tick, 2, sf::PrimitiveType::Lines);

            std::ostringstream ss;
            ss << (int)v << "m";
            panel.drawText(ss.str(), {sp.x - 10.f, sp.y - 15.f}, 15, sf::Color{130, 130, 145});
        }
    }

    void drawBall(const Model& model) {
        int n   = model.solution.GetLenght();
        int idx = std::min((int)(model.animT * n), n - 1);
        auto pt  = model.solution.Get(idx);
        auto sfp = model.cm.toScreen((float)pt[0], (float)pt[1]);
        Vec2f sp = {sfp.x, sfp.y};
        sf::CircleShape ball(6.f);
        ball.setOrigin({6.f, 6.f});
        ball.setPosition({sp[0], sp[1]});
        ball.setFillColor(ACCENT);
        window.draw(ball);
    }

    void drawScene(Model& model) {
        panel.drawRect({CX, CY}, {CW, CH}, {28, 28, 34}, BORDER, 1.f);
        drawAxes(model.cm);
        for (auto& t : model.tries)
            drawTrajectory(t, model.cm, TRY_COL);
        if (model.hasSolution) {
            drawTrajectory(model.solution, model.cm, ACCENT);
            drawBall(model);
        }
    }
};