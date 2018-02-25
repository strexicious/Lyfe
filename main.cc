#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "gol.hh"

using namespace std;

constexpr unsigned WIDTH = 500;
constexpr unsigned HEIGHT = 500;

int main() {

    GoL<HEIGHT, WIDTH>::Grid random_state;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dist;
    for (unsigned i = 0; i < random_state.size(); ++i) {
        for (unsigned j = 0; j < random_state[0].size(); ++j) {
            random_state[i][j] = (bool) dist(gen);
        }
    }

    GoL<HEIGHT, WIDTH> gol(random_state);
    GoL<HEIGHT, WIDTH>::Grid gol_state = gol.state();

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Lyfe");
    window.setFramerateLimit(30);
    sf::Image gol_draw;
    gol_draw.create(WIDTH, HEIGHT);
    sf::Texture gol_text;
    gol_text.loadFromImage(gol_draw);
    sf::Sprite gol_spr(gol_text);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
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

        gol_text.update(gol_draw);

        window.clear();
        window.draw(gol_spr);
        window.display();
        gol_state = gol.update();
    }

    return 0;
}
