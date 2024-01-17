// Block.cpp
#include "Block.h"
#include "Player.h"
#include <iostream>

Block::Block(float x, float y, float width, float height, sf::Texture& texture)
    : sprite()
{
    sprite.setPosition(x, y);
    sprite.setTexture(texture);
    sprite.setScale(4.0f, 2.0f);
}

void Block::render(sf::RenderWindow& window) const {
    window.draw(sprite);
}

float Block::getY() const {
    return sprite.getPosition().y;
}

void Block::moveDown(float distance) {
    sprite.move(0.0f, distance);
}

void Block::update(float deltaTime) {
    // Aktualizacja logiki bloku, jeœli to konieczne
}

sf::FloatRect Block::getBoundingBox() const {
    return sprite.getGlobalBounds();
}
