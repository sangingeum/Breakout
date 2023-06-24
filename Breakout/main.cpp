#include <iostream>
#include <format>
#include <SFML/Graphics.hpp>
#include "Vec2.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setPosition(100.0f, 100.0f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                shape.setFillColor(sf::Color::Red);
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                shape.setFillColor(sf::Color::Green);
            }

        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}