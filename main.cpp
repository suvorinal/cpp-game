#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "./Objects/Player.cpp"
#include "./Objects/Menu.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 800), "SFML window");
    window.setFramerateLimit(60);

    Menu menu;

    Player player;
    Map map;

    float dX = 0;
    float dY = 0;

    sf::Clock clock;
    sf::Time frameTime{ sf::Time::Zero };


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f pos = window.mapPixelToCoords(pixelPos);

        window.clear(sf::Color(255, 255, 255, 255));

        if (!menu.getIsOpen()) {

            if (event.type == sf::Event::MouseButtonPressed)
                if (event.key.code == sf::Mouse::Left)
                    if (player.getPosition().contains(pos.x, pos.y)) {
                        player.setIsDrag(true);
                        dX = pos.x - player.getPosition().left;
                        dY = pos.y - player.getPosition().top;
                    }

            if (event.type == sf::Event::MouseButtonReleased)
                if (event.key.code == sf::Mouse::Left)
                    player.setIsDrag(false);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) menu.open();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.jump();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) player.hit();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.walkRight();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.walkLeft();
            else player.stay();

            map.draw(window);

            player.update(frameTime.asMilliseconds());
            player.drag(pos.x - dX, pos.y - dY);
            player.draw(window);
        } else {
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.key.code == sf::Mouse::Left) {
                    bool isCloseWindow = menu.isCloseWindow(pos.x, pos.y);
                    if (isCloseWindow) {
                        window.close();
                    }
                }

            menu.onMouseOver(pos.x, pos.y);
            menu.update();
            menu.draw(window);
        }

        frameTime = clock.restart();
        window.display();
    }

    return EXIT_SUCCESS;
}