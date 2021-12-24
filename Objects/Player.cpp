#include <SFML/Graphics.hpp>
#include "./Map.cpp"

class Player {
    private:
        Map *map = new Map();
        sf::Sprite sprite;

        sf::RectangleShape healthRect;
        float health = 100;

        sf::Texture idle; // 0
        sf::Texture attack; // 1
        sf::Texture death; // 2
        sf::Texture hurt; // 3
        sf::Texture walk; // 4
        int currentSprite = -1;
        int spriteNum = 0;
        int spriteWidth = 84;
        int spriteHeight = 97;
        int spriteDelay = 0;
        int spriteDelayFrames = 8;

        int walkDirection = 0;

        float x = 200;
        float y = 200;
        float dy = 0;
        float dx = 0;

        bool isAlive = true;
        bool onGround = false;
    public:

    sf::Rect<float> getPosition() { return sprite.getGlobalBounds(); }

    void loadTextures() {
        idle.loadFromFile("..\\Textures\\Idle.png");
        attack.loadFromFile("..\\Textures\\Attack.png");
        death.loadFromFile("..\\Textures\\Death.png");
        hurt.loadFromFile("..\\Textures\\Hurt.png");
        walk.loadFromFile("..\\Textures\\Walk.png");
    }

    void stay() {
        if (!isAlive) return;
        if (currentSprite != 0) {
            currentSprite = 0;
            sprite.setTexture(idle);
            spriteWidth = 84;
            spriteHeight = 97;
            spriteNum = 0;
        }
    }

    void die() {
        isAlive = false;
        if (currentSprite != 2) {
            spriteDelayFrames = 25;
            currentSprite = 2;
            sprite.setTexture(death);
            spriteWidth = 94;
            spriteHeight = 75;
            spriteNum = 0;
        }
    }

    void walkRight() {
        if (!isAlive) return;
        dx += 5;
        walkDirection = 0;
        if (currentSprite != 4) {
            currentSprite = 4;
            sprite.setTexture(walk);
            spriteWidth = 83;
            spriteHeight = 95;
            spriteNum = 0;
        }
    }

    void walkLeft() {
        if (!isAlive) return;
        dx -= 5;
        walkDirection = 1;
        if (currentSprite != 4) {
            currentSprite = 4;
            sprite.setTexture(walk);
            spriteWidth = 83;
            spriteHeight = 95;
            spriteNum = 0;
        }
    }

    void jump() {
        if (onGround && isAlive) {
            dy -= 50;
            onGround = false;
        }
    }

    void nextSprite() {
        if (spriteDelay < spriteDelayFrames) {
            spriteDelay++;
            return;
        } else {
            spriteDelay = 0;
        }
        switch (currentSprite) {
            case 0:
                if (spriteNum < 2) spriteNum++;
                else spriteNum = 0;
                break;
            case 1:
                if (spriteNum < 3) spriteNum++;
                else spriteNum = 0;
                break;
            case 2:
                if (spriteNum < 3) spriteNum++;
                break;
            case 3:
                if (spriteNum < 2) spriteNum++;
                else spriteNum = 0;
                break;
            case 4:
                if (spriteNum < 5) spriteNum++;
                else spriteNum = 0;
                break;
        }
    }

    Player() {
        loadTextures();
        stay();

        healthRect.setFillColor(sf::Color::Green);
        healthRect.setSize(sf::Vector2<float>(health, 25.0));
    }

    void update() {
        nextSprite();
        if (!walkDirection) {
            sprite.setTextureRect(sf::Rect<int>(spriteNum * spriteWidth, 0, spriteWidth, spriteHeight));
        } else {
            sprite.setTextureRect(sf::Rect<int>(spriteWidth + spriteNum * spriteWidth, 0, -spriteWidth, spriteHeight));
        }
        if (!isAlive) return;
        float prevY = y;
        if (dy > 10) y += 10;
        else if (dy < -10) y += -10;
        else y += dy;
        sf::Rect<float> rect(x, y, spriteWidth-1, spriteHeight);
        if (map->isNextCollide(rect)) {
            y = prevY;
            onGround = true;
            dy = 0;
        } else {
            dy += 5;
        }

        rect = sf::Rect<float>(x + dx, y, spriteWidth, spriteHeight);
        if (!map->isNextCollide(rect)) {
            x += dx;
            if (dx < -5) {
                dx += 5;
            } else if (dx > 5) {
                dx -= 5;
            } else {
                dx = 0;
            }
        } else {
            dx = 0;
        }

        health -= 0.5;
        if (health < 0) {
            die();
        }
        sprite.setPosition(x, y);
    }

    void draw(sf::RenderWindow &window) {
        sf::Rect<float> playerPosition = getPosition();
        healthRect.setPosition(playerPosition.left + (playerPosition.width - health) / 2, playerPosition.top - 35);
        healthRect.setSize(sf::Vector2<float>(health, 25.0));
        window.draw(healthRect);
        window.draw(sprite);
    }
};