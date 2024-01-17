// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Block.h"  // Dodaj nag³ówek z klas¹ Block

class Player {
public:
    Player(const std::string& windowTitle, int screenWidth, int screenHeight);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void moveLeft();
    void moveRight();
    void jump();

    // Nowo dodane metody
    void bounceUp();
    bool isCollidingWith(const Block& block) const;
    bool isMovingDown() const;

private:
    void updatePosition(float deltaTime);

    sf::Texture texture;
    sf::Sprite sprite;
    float velocityX;
    float velocityY;
    bool isJumping;
    float gravity;
    float jumpHeight;
    bool onGround;
    int screenWidth;  // Dodana szerokoœæ ekranu
};

#endif
