// Block.h
#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

class Block {
public:
    Block(float x, float y, float width, float height, const std::string& texturePath);

    void render(sf::RenderWindow& window) const;

private:
    sf::RectangleShape shape;
    sf::Texture texture;
};

#endif
