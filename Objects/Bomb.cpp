#include <SFML/Graphics.hpp>

class Bomb {
private:
    float x = 0, y = 0;
    sf::Texture t;
    sf::Sprite sprite;

    bool isAlive = true;

    void loadTexture() {
        t.loadFromFile("..\\Textures\\bomb.png");
        sprite.setTexture(t);
    }

public:
    Bomb(float x, float y) {
        this->x = x;
        this->y = y;
        loadTexture();
        sprite.setPosition(x, y);
        sprite.setScale(0.5, 0.5);
    }

    void blowUp() {
        isAlive = false;
    }

    bool getIsAlive() { return isAlive; }

    sf::Rect<float> getPosition() { return sprite.getGlobalBounds(); }

    void draw(sf::RenderWindow &window) {
        if (isAlive) {
            window.draw(sprite);
        }
    }
};