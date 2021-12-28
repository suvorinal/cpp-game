#include <SFML/Graphics.hpp>

class Heart {
private:
    float x = 0, y = 0;
    sf::Texture t;
    sf::Sprite sprite;

    bool isAlive = true;

    void loadTexture() {
        t.loadFromFile("..\\Textures\\heart.png");
        sprite.setTexture(t);
    }

public:
    Heart(float x, float y) {
        this->x = x;
        this->y = y;
        loadTexture();
        sprite.setPosition(x, y);
        sprite.setScale(0.5, 0.5);
    }

    void heal() {
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