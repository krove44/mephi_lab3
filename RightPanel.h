#pragma once
#include <SFML/Graphics.hpp>
#include "Model.h"

using Vec2f = Vec<ArraySequence, float, 2>;

struct RightPanel {
    sf::RenderWindow& window;
    sf::Font& font;

    RightPanel(sf::RenderWindow& w, sf::Font& f) : window(w), font(f) {}

    void drawText(const std::string& str, Vec2f pos, unsigned size = 14, sf::Color color = TEXT_PRI) {
        sf::Text t(font, str, size);
        t.setFillColor(color);
        t.setPosition({pos[0], pos[1]});
        window.draw(t);
    }

    void drawRect(Vec2f pos, Vec2f size, sf::Color fill, sf::Color outline = sf::Color::Transparent, float thickness = 0.f) {
        sf::RectangleShape r({size[0], size[1]});
        r.setPosition({pos[0], pos[1]});
        r.setFillColor(fill);
        if (thickness > 0.f) {
            r.setOutlineColor(outline);
            r.setOutlineThickness(thickness);
        }
        window.draw(r);
    }

    void drawField(const Field& f) {
        drawRect({f.x, f.y}, {f.w, 30.f}, {40, 40, 50}, f.active ? ACCENT : BORDER, 1.f);
        drawText(f.label, {f.x + 2.f,  f.y - 26.f}, 20, TEXT_SEC);
        drawText(f.value + (f.active ? "|" : ""), {f.x + 8.f, f.y + 7.f}, 16);
    }

    void drawButton(const Button& b, sf::Color fill = ACCENT) {
        drawRect({b.x, b.y}, {b.w, b.h}, fill);
        sf::Text t(font, b.label, 14);
        t.setFillColor(sf::Color::White);
        auto tb = t.getLocalBounds();
        t.setPosition({
            b.x + (b.w - tb.size.x) / 2.f - tb.position.x,
            b.y + (b.h - tb.size.y) / 2.f - tb.position.y
        });
        window.draw(t);
    }

    void drawPanel(Model& model) {
        drawRect({0, 0},   {PANEL_W, WIN_H}, PANEL_BG);
        drawText("Parameters:", {PAD, 16.f}, 20, TEXT_SEC);
        for (auto& f : model.fields) {
            drawField(f);
        }
        drawButton(model.calcBtn, model.btnPressed ? sf::Color{20, 110, 82} : ACCENT);

        if (model.hasSolution) {
            auto fmt = [](double v, int p = 2) {
                std::ostringstream s;
                s << std::fixed << std::setprecision(p) << v;
                return s.str();
            };
            float ry = model.calcBtn.y + 50.f;
            drawText("v0    = " + fmt(model.result.v0) + " m/s", {PAD, ry}, 18, model.statusColor);
            drawText("angle = " + fmt(model.result.angle*180.0/PI, 1) + " deg", {PAD, ry + 18.f}, 18, model.statusColor);
            drawText("range = " + fmt(model.result.range, 1) + " m", {PAD, ry + 36.f}, 18, model.statusColor);
        }
    }
};