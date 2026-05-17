#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1280u, 720u}),
        "Trajectory Gui",
        sf::Style::Titlebar | sf::Style::Close
    );
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (const auto ev = window.pollEvent())
        {
            if (ev->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color{24, 24, 28});
        window.display();
    }

    return 0;
}