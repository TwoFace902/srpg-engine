#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <conio.h>

int main()
{
    std::string ASSET_PATH = "assets\\";
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "hell");
    sf::Texture testtex;
    sf::Music pain;
    if (!pain.openFromFile(ASSET_PATH + "pain.ogg")) {
        return -2;
    }
    if (!testtex.loadFromFile(ASSET_PATH + "dlight.png")) {
        return -1;
    }
    sf::Sprite testsprite;
    testsprite.setTexture(testtex);
    pain.play();
    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            testsprite.move(0.f, -0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            testsprite.move(0.f, 0.1f);
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(testsprite);
        window.display();
    }

    return 0;
}