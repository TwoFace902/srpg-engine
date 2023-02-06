#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <conio.h>
#include "Map.h"

int main()
{
    std::string ASSET_PATH = "assets\\";

    // define the level with an array of tile indices
    const int level[] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };
    int width = 16;
    int height = 8;
    sf::Vector2<int> pos(0, 0);
    Map map;
    if (!map.load(ASSET_PATH + "tileset.png", sf::Vector2u(64, 64), level, 16, 8)) {
        return -3;
    }
    sf::RenderWindow window(sf::VideoMode(1600, 800), "hell");
    sf::Texture testtex;
    sf::Music pain;
    sf::Text location;
    sf::Clock tick;
    float cooldown = 0.1f;
    if (!pain.openFromFile(ASSET_PATH + "pain.ogg")) {
        return -2;
    }
    if (!testtex.loadFromFile(ASSET_PATH + "dlight.png")) {
        return -1;
    }

    sf::Sprite testsprite;
    testsprite.setTexture(testtex);
    const sf::Vector2f spriteSize(
        testsprite.getTexture()->getSize().x * testsprite.getScale().x,
        testsprite.getTexture()->getSize().y * testsprite.getScale().y);
    testsprite.setScale(64/spriteSize.x, 64/spriteSize.y);
    pain.play();
    while (window.isOpen())
    {
        if (cooldown <= 0.f) {
            bool moved = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                pos += sf::Vector2<int>(0, -1);
                moved = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                pos += sf::Vector2<int>(0, 1);
                moved = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                pos += sf::Vector2<int>(-1, 0);
                moved = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                pos += sf::Vector2<int>(1, 0);
                moved = true;
            }
            if (moved) {
                cooldown = 0.1f;
            }
        }
        sf::Time delta = tick.restart();
        cooldown -= delta.asSeconds();
        testsprite.setPosition(pos.x * 64, pos.y * 64);
        //do bound checking
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        location.setString(std::to_string(pos.x) + ", " + std::to_string(pos.y));
        window.clear();
        window.draw(map);
        window.draw(location);
        window.draw(testsprite);
        window.display();
    }

    return 0;
}