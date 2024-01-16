// Block.cpp
#include "Block.h"
#include <iostream>

Block::Block(float x, float y, float width, float height, const std::string& texturePath) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "B³¹d ³adowania tekstury: " << texturePath << std::endl;
    }

    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setTexture(&texture);
    //shape.setScale(4.0f, 2.0f);
}

void Block::render(sf::RenderWindow& window) const {
    window.draw(shape);
}

float Block::getX() const {
    return shape.getPosition().x;
}

float Block::getWidth() const {
    return shape.getSize().x;
}

float Block::getY() const {
    return shape.getPosition().y;
}

float Block::getHeight() const {
    return shape.getSize().y;
}

void Block::update(float deltaTime) {
    float fallSpeed = 200.0f;
    shape.move(0.0f, fallSpeed * deltaTime);
}
