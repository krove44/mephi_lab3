#include <SFML/Graphics.hpp>
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

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({static_cast<unsigned int>(WIN_W), static_cast<unsigned int>(WIN_H)}),
        "Trajectory Gui",
        sf::Style::Titlebar | sf::Style::Close
    );
    window.setFramerateLimit(60);

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



    while (window.isOpen())
    {
        while (const auto ev = window.pollEvent())
        {
            if (ev->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color{24, 24, 28});

        drawRect(0, 0, PANEL_W, WIN_H, PANEL_BG);
        drawText("Parameters", PAD, 16.f, 20, TEXT_SEC);

        drawRect(CX, CY, CW, CH, {28, 28, 34}, BORDER, 1.f);
        drawText("Graph of moving", CX + 10.f, CY + 10.f, 20, TEXT_SEC);

        window.display();
    }

    return 0;
}