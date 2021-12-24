#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "./Objects/Player.cpp"
#include "./Objects/Bomb.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 800), "SFML window");
    window.setFramerateLimit(60);


    Player player;
    Map map;

    Bomb bomb;

    int delay = 0;
    float dX = 0;
    float dY = 0;

    while (window.isOpen())
    {
        if (delay < 2) {
            delay++;
            continue;
        } else {
            delay = 0;
        }


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f pos = window.mapPixelToCoords(pixelPos);

        if (event.type == sf::Event::MouseButtonPressed)
            if (event.key.code == sf::Mouse::Left)
                if (bomb.getPosition().contains(pos.x, pos.y)) {
                    bomb.setMove(true);
                    dX = pos.x - bomb.getPosition().left;
                    dY = pos.y - bomb.getPosition().top;
                }

        if (event.type == sf::Event::MouseButtonReleased)
            if (event.key.code == sf::Mouse::Left)
                bomb.setMove(false);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.jump();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.walkRight();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.walkLeft();
        else player.stay();
        window.clear(sf::Color(255,255,255,255));

        map.draw(window);
        player.update();
        player.draw(window);

        bomb.update(pos.x - dX, pos.y - dY);
        bomb.draw(window);

        window.display();
    }

    return EXIT_SUCCESS;
}