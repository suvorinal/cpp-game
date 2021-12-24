#include <iostream>
#include <SFML/Graphics.hpp>

const int Height = 25;
const int Width = 40;
const int SideLength = 32;

class Map {
    private:
        sf::Texture tiles;
        sf::Sprite sprite;
        sf::RectangleShape square;

        std::string map[Height] = {
                "7                                      6",
                "7                                      6",
                "7                                      6",
                "7                                      6",
                "7                                      6",
                "7                                      6",
                "7                                      6",
                "7                                      6",
                "7                                      6",
                "7                                      6",
                "7                                      6",
                "7                             33333    6",
                "7                             00000    6",
                "7                                      6",
                "7             333333                   6",
                "7             000000                   6",
                "7                                      6",
                "7   233333333333333333333333333333333330",
                "7   600000000000000000000000000000000000",
                "0333000000000000000000000000000000000000",
                "0000000000000000000000000000000000000000",
                "0000000000000000000000000000000000000000",
                "0000000000000000000000000000000000000000",
                "0000000000000000000000000000000000000000",
                "0000000000000000000000000000000000000000",
        };

        void loadMapTiles() {
            tiles.loadFromFile("..\\Textures\\Tiles.png");
            sprite.setScale(1.0 / 16, 1.0 / 16);
        }

    public:
        Map() {
            loadMapTiles();
            sprite.setTexture(tiles);
        }

        bool isNextCollide(sf::Rect<float> &rect) {
            bool flag = false;
            for (int i = 0; i < Height; i++) {
                for (int j = 0; j < Width; j++) {
                    if (map[i][j] == ' ') {
                        continue;
                    }

                    sf::Rect<float> tileRect((float) SideLength * j, (float) SideLength * i, (float) SideLength,
                                             (float) SideLength);


                    if (rect.intersects(tileRect)) {
                        flag = true;
                    }
                }
            }
            return flag;
        }

    void draw(sf::RenderWindow &window) {
        for (int i = 0; i < Height; i++)
            for (int j = 0; j < Width; j++)
            {
                if (map[i][j] == ' ') {
                    square.setFillColor(sf::Color::White);
                    square.setPosition((float)SideLength * j, (float)SideLength * i);
                    window.draw(square);
                } else {
                    int textureNum = map[i][j] - '0';
                    sprite.setTextureRect(sf::Rect<int>(512 * textureNum, 0, 512, 512));
                    sprite.setPosition((float) SideLength * j, (float) SideLength * i);
                    window.draw(sprite);
                }
            }
    }
};