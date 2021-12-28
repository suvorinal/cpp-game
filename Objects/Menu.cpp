#include <iostream>
#include <SFML/Graphics.hpp>

class Menu {
private:
    sf::Text start;
    sf::Text exit;
    sf::Font font;
    sf::Texture bg;
    sf::Sprite bgSprite;

    bool isOpen = true;

    void loadFont() {
        if (!font.loadFromFile("..\\Textures\\ARCADECLASSIC.TTF")) {
            std::cout << "ERROR!" << std::endl;
        }
    }

    void loadBg() {
        bg.loadFromFile("..\\Textures\\MenuBG.png");
        bgSprite.setTexture(bg);
        bgSprite.setScale(0.75, 0.75);
    }

    void initStart() {
        start.setFont(font);
        start.setString("START GAME!!");
        start.setCharacterSize(56);
        start.setFillColor(sf::Color::Red);
        start.setStyle(sf::Text::Bold);
        sf::Rect<float> position = start.getGlobalBounds();
        start.setPosition((1280 - position.left - position.width) / 2, 0);
    }

    void initExit() {
        exit.setFont(font);
        exit.setString("EXIT");
        exit.setCharacterSize(56);
        exit.setFillColor(sf::Color::Red);
        exit.setStyle(sf::Text::Bold);
        sf::Rect<float> position = exit.getGlobalBounds();
        exit.setPosition((1280 - position.left - position.width) / 2, 100);
    }

public:
    Menu() {
        loadBg();
        loadFont();
        initStart();
        initExit();
    }

    bool getIsOpen() { return isOpen; }
    void open() { isOpen = true; }
    void close() { isOpen = false; }

    void update() {
        if (start.getPosition().y < 300) {
            exit.move(0, 10);
            start.move(0, 10);
        }
    }

    void onMouseOver(float x, float y) {
        sf::Rect<float> rect(x, y, 1, 1);
        if (start.getGlobalBounds().intersects(rect)) {
            start.setStyle(sf::Text::Bold | sf::Text::Underlined);
        } else {
            start.setStyle(sf::Text::Bold);
        }

        if (exit.getGlobalBounds().intersects(rect)) {
            exit.setStyle(sf::Text::Bold | sf::Text::Underlined);
        } else {
            exit.setStyle(sf::Text::Bold);
        }
    }

    bool isCloseWindow(float x, float y) {
        sf::Rect<float> rect(x, y, 1, 1);
        if (start.getGlobalBounds().intersects(rect)) {
            close();
        }

        if (exit.getGlobalBounds().intersects(rect)) {
            return true;
        }

        return false;
    }

    void draw(sf::RenderWindow &window) {
        window.draw(bgSprite);
        window.draw(start);
        window.draw(exit);
    }
};