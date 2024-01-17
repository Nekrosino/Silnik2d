// Block.h
#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

class Block {
public:
    Block(float x, float y, float width, float height, sf::Texture& texture);

    void render(sf::RenderWindow& window) const;
    float getY() const;
    void moveDown(float distance);
    void update(float deltaTime);
    sf::FloatRect getBoundingBox() const;

private:
    sf::Sprite sprite;
};

#endif
