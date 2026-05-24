#pragma once
#include <SFML/Graphics.hpp>
#include "Model.h"

struct EventHandler {
    static bool btnContains(const Button& b, sf::Vector2f mp) {
        return sf::FloatRect{{b.x, b.y}, {b.w, b.h}}.contains(mp);
    }

    void handle(sf::RenderWindow& window, Model& model) {
        while (const auto ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>())
                window.close();
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
    }
};