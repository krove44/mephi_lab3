#include <SFML/Graphics.hpp>
#include "gui/Model.h"
#include "gui/RightPanel.h"
#include "gui/LeftPanel.h"
#include "gui/EventHandler.h"

int main() {
    sf::RenderWindow window(
        sf::VideoMode({static_cast<unsigned int>(WIN_W), static_cast<unsigned int>(WIN_H)}),
        "Trajectory Gui"
    );
    window.setFramerateLimit(60);

    sf::Clock clock;
    sf::Font font;
    font.openFromFile("assets/Roboto/Roboto-VariableFont_wdth,wght.ttf");
    Model model;
    RightPanel panel(window, font);
    LeftPanel scene(window, panel);
    EventHandler events;

    while (window.isOpen()) {
        model.btnPressed = false;
        model.update(clock.restart().asSeconds());
        events.handle(window, model);

        window.clear(BG);
        panel.drawPanel(model);
        scene.drawScene(model);
        window.display();
    }

    return 0;
}