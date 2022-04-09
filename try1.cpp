//Source Code:
//Standard C++:
#include <iostream>
//SFML:
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Example");

    sf::Event event;

    sf::RectangleShape mousePoint;
    mousePoint.setSize(sf::Vector2f(1, 1));
    mousePoint.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) //Close window
            {
                window.close();
                return 0;
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // //Get the mouse position:
                    // sf::Vector2i mouse = sf::Mouse::getPosition(window);
                    // //Map Pixel to Coords:
                    // window.mapPixelToCoords(mouse);
                    // //Set position of the mouse to the rectangle:
                    // mousePoint.setPosition(mouse.x, mouse.y);
                    //Get the mouse position:
                    sf::Vector2i mouse = sf::Mouse::getPosition(window);
                    //Map Pixel to Coords:
                    sf::Vector2f mouse_world = window.mapPixelToCoords(mouse);
                    //Set position of the mouse to the rectangle:
                    mousePoint.setPosition(mouse_world);
                }
            }
        }

        window.clear();
        window.draw(mousePoint);
        window.display();
    }
}