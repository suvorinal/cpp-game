#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "./Map.cpp"
#include "./Wall.cpp"

class Player {
    private:
        Map *map = new Map();
        Wall *wall;
        sf::Sprite sprite;

        sf::RectangleShape healthRect;
        float health = 100;

        sf::SoundBuffer hitSoundBuffer;
        sf::Sound hitSound;
        sf::Texture idle; // 0
        sf::Texture attack; // 1
        sf::Texture death; // 2
        sf::Texture hurt; // 3
        sf::Texture walk; // 4
        int currentSprite = -1;
        int spriteNum = 0;
        int spriteWidth = 84;
        int spriteHeight = 97;
        float spriteDelay = 0;
        float spriteDelayFrames = 80;

        int walkDirection = 0;

        float x = 200;
        float y = 200;
        float vy = 0;
        float dx = 0;
        float mass = 1.25;
        float const g = 9.81;
        float aY = 0;
        bool isDragging = false;

    bool isAlive = true;
        bool onGround = false;

    void loadSound() {
        hitSoundBuffer.loadFromFile("..\\Textures\\hitSound.wav");
        hitSound.setBuffer(hitSoundBuffer);
    }

    void loadTextures() {
        idle.loadFromFile("..\\Textures\\Idle.png");
        attack.loadFromFile("..\\Textures\\Attack.png");
        death.loadFromFile("..\\Textures\\Death.png");
        hurt.loadFromFile("..\\Textures\\Hurt.png");
        walk.loadFromFile("..\\Textures\\Walk.png");
    }

    bool isCollideWithMap(float x, float y) {
        sf::Rect<float> rect(x, y, spriteWidth-1, spriteHeight);
        return map->isNextCollide(rect);
    }

    void nextSprite(float ms) {
        spriteDelay += ms;
        if (spriteDelay < spriteDelayFrames) {
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
                else {
                    currentSprite = -1;
                    stay();
                }
                break;
            case 2:
                if (spriteNum < 3) spriteNum++;
                break;
            case 3:
                if (spriteNum < 1) spriteNum++;
                else {
                    currentSprite = -1;
                    spriteDelayFrames = 80;
                    stay();
                }
                break;
            case 4:
                if (spriteNum < 5) spriteNum++;
                else spriteNum = 0;
                break;
        }
    }

    void handleGravity(float ms) {
        if (!ms) return;
        vy += (g + aY) / (ms * mass);
        float tempY = y + vy;
        onGround = isCollideWithMap(x, tempY);
        if (onGround) {
            aY = 0;
            vy = 0;
        } else {
            y = tempY;
            aY--;
            if (aY < 0) aY = 0;
        }
    }

    public:

    sf::Rect<float> getPosition() { return sprite.getGlobalBounds(); }

    void blowUp() {
        health -= 50;
        if (!isAlive) return;
        if (currentSprite != 3) {
            currentSprite = 3;
            spriteDelayFrames = 250;
            sprite.setTexture(hurt);
            spriteWidth = 81;
            spriteHeight = 85;
            spriteNum = 0;
        }
    }

    void heal() {
        health += 50;
        if (health > 100) {
            health = 100;
        }
    }

    void stay() {
        if (!isAlive || currentSprite == 1 || currentSprite == 3) return;
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
            spriteDelayFrames = 800;
            currentSprite = 2;
            sprite.setTexture(death);
            spriteWidth = 94;
            spriteHeight = 75;
            spriteNum = 0;
        }
    }

    void hit() {
        if (!isAlive) return;
        if (currentSprite != 1) {
            sf::Rect<float> r = getPosition();
            if (!walkDirection) {
                r = sf::Rect<float>(r.left, r.top, r.width + 20, r.height);
            } else {
                r = sf::Rect<float>(r.left - 20, r.top, r.width, r.height);
            }
            wall->hit(r);
            currentSprite = 1;
            hitSound.play();
            sprite.setTexture(attack);
            spriteWidth = 103;
            spriteHeight = 97;
            spriteNum = 0;
        }
    }

    void walkRight() {
        if (!isAlive || currentSprite == 3) return;
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
        if (!isAlive || currentSprite == 3) return;
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
            aY = -250;
            onGround = false;
        }
    }

    Player(Wall * wall) {
        this->wall = wall;
        loadTextures();
        loadSound();
        stay();

        healthRect.setFillColor(sf::Color::Green);
        healthRect.setSize(sf::Vector2<float>(health, 25.0));
    }

    void drag(float dx, float dy) {
        if (isDragging) {
            x = dx;
            y = dy;
            sprite.setPosition(x, y);
        }
    }
    void setIsDrag(bool flag) { isDragging = flag; }

    void update(float ms) {
        nextSprite(ms);
        if (!walkDirection) {
            sprite.setTextureRect(sf::Rect<int>(spriteNum * spriteWidth, 0, spriteWidth, spriteHeight));
        } else {
            sprite.setTextureRect(sf::Rect<int>(spriteWidth + spriteNum * spriteWidth, 0, -spriteWidth, spriteHeight));
        }
        if (!isAlive || isDragging) return;

        handleGravity(ms);

        sf::Rect<float> rect = sf::Rect<float>(x + dx, y, spriteWidth, spriteHeight);
        if (!map->isNextCollide(rect) && !wall->isNextCollide(rect)) {
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

        //health -= 0.5;
        if (health < 0.1) {
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