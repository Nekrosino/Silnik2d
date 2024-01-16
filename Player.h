// Player.h

#pragma once

#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float velocityX;
    float velocityY;
    bool isJumping;
    float gravity;
    float jumpHeight;
    bool onGround;
    int screenWidth;

public:
    Player(const std::string& windowTitle, int screenWidth, int screenHeight);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    void moveLeft();
    void moveRight();
    void jump();

    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    bool getOnGround() const;
    bool getIsJumping() const;
};
