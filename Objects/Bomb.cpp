#include <SFML/Graphics.hpp>

class Bomb {
private:
    sf::Texture bombTexture;
    sf::Sprite bomb;

    float x = 0, y = 0;
    bool isMoving = false;
    void loadTexture() {
        bombTexture.loadFromFile("..\\Textures\\Bomb.png");
    }

public:
    Bomb() {
        loadTexture();
        bomb.setTexture(bombTexture);
        bomb.setScale(0.125, 0.125);
    }

    sf::Rect<float> getPosition() { return bomb.getGlobalBounds(); }
    void setMove(bool flag) { isMoving = flag; }
    bool getMove() { return isMoving; }

    void update(float dx, float dy) {
        if (isMoving) {
            x = dx;
            y = dy;
            bomb.setPosition(x, y);
        }
    }

    void draw(sf::RenderWindow &window) {
        window.draw(bomb);
    }
};