#include <SFML/Graphics.hpp>
#include <iostream>

class Wall {
private:
    sf::Texture wallT;
    sf::Sprite wall;

    float health = 100;
    sf::RectangleShape healthRect;

    void loadTexture() {
        wallT.loadFromFile("..\\Textures\\wall.png");
        wall.setTexture(wallT);
        wall.setScale(0.25, 0.25);
        wall.setPosition(500, 685);
    }

public:
    Wall() {
        loadTexture();
        healthRect.setFillColor(sf::Color::Red);
    }

    void hit(sf::Rect<float> playerRect) {
        if (health > 0 && wall.getGlobalBounds().intersects(playerRect)) {
            health -= 20;
        }
    }

    bool isNextCollide(sf::Rect<float> &rect) {
        return health > 0 && rect.intersects(wall.getGlobalBounds());
    }

    void draw(sf::RenderWindow &window) {
        if (health > 0) {
            sf::Rect<float> wallPosition = wall.getGlobalBounds();
            healthRect.setPosition(wallPosition.left + (wallPosition.width - health) / 2, wallPosition.top - 25);
            healthRect.setSize(sf::Vector2<float>(health, 12.0));
            window.draw(healthRect);
            window.draw(wall);
        }
    }
};