// Block.h
#pragma once

#include <SFML/Graphics.hpp>

class Block {
private:
    sf::RectangleShape shape;
    sf::Texture texture;

public:
    Block(float x, float y, float width, float height, const std::string& texturePath);

    void render(sf::RenderWindow& window) const;
    float getX() const;
    float getWidth() const;
    float getY() const;
    float getHeight() const; // Dodaj tê liniê
    void update(float deltaTime);
};
