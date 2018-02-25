#include <iostream>
#include <SFML/Graphics.hpp>
#include "gol.hh"

using namespace std;

constexpr unsigned WIDTH = 10;
constexpr unsigned HEIGHT = 10;

int main() {
    const GoL<HEIGHT, WIDTH>::Grid pattern = {{
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, true , false, false, false, false},
        {false, false, false, true , false, true , false, false, false, false},
        {false, false, false, false, true , true , false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false, false},
    }};

    GoL<HEIGHT, WIDTH> gol(pattern);
    GoL<HEIGHT, WIDTH>::Grid gol_state = gol.state();

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML window");
    window.setFramerateLimit(10);
    sf::Image gol_draw;
    gol_draw.create(WIDTH, HEIGHT);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (unsigned i = 0; i < HEIGHT; i++) {
            for (unsigned j = 0; j < WIDTH; ++j) {
                if (gol_state[i][j])
                    gol_draw.setPixel(j, i, sf::Color(0xffffffff));
                else
                    gol_draw.setPixel(j, i, sf::Color(0x000000ff));
            }
        }

        sf::Texture gol_text;
        gol_text.loadFromImage(gol_draw);
        sf::Sprite sprite(gol_text);

        window.clear();
        window.draw(sprite);
        window.display();
        gol_state = gol.update();
    }


    return 0;
}
