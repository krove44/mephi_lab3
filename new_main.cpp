#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1280u, 720u}),
        "Trajectory Gui",
        sf::Style::Titlebar | sf::Style::Close
    );
    window.setFramerateLimit(60);

    sf::Font font;
    auto check = font.openFromFile("C:/Windows/Fonts/segoeui.ttf");


    auto drawText = [&](const std::string& str, float x, float y, unsigned size = 14, sf::Color color = sf::Color{220, 220, 225}) {
        sf::Text t(font, str, size);
        t.setFillColor(color);
        t.setPosition({x, y});
        window.draw(t);
    };

    while (window.isOpen())
    {
        while (const auto ev = window.pollEvent())
        {
            if (ev->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color{24, 24, 28});

        drawText("Trajectory Gui", 20.f, 20.f, 24);
        drawText("Parameters",            20.f, 60.f, 20, sf::Color{130, 130, 145});
        drawText("v0 = 45 m/s",           20.f, 90.f, 16);

        window.display();
    }

    return 0;
}