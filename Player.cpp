// Player.cpp
#include "Player.h"
#include <iostream>

Player::Player(const std::string& windowTitle, int screenWidth, int screenHeight)
    : velocityX(0.0f), velocityY(0.0f), isJumping(false), gravity(2000.0f), jumpHeight(400.0f), onGround(true),
    screenWidth(screenWidth)
{
    if (!texture.loadFromFile("textures/test.png")) {
        std::cerr << "Nie mo¿na za³adowaæ tekstury postaci." << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setPosition(screenWidth / 2.0f, screenHeight - 50.0f);
}

void Player::update(float deltaTime) {
    updatePosition(deltaTime);
}

void Player::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::moveLeft() {
    velocityX = -600.0f;
}

void Player::moveRight() {
    velocityX = 600.0f;
}

void Player::jump() {
    if (onGround) {
        velocityY = -sqrt(2.0f * gravity * jumpHeight);
        isJumping = true;
        onGround = false;
    }
}

void Player::bounceUp() {
    velocityY = -sqrt(2.0f * gravity * jumpHeight);
    isJumping = true;
    onGround = false;
}

bool Player::isCollidingWith(const Block& block) const {
    return sprite.getGlobalBounds().intersects(block.getSprite().getGlobalBounds());
    // Za³ó¿my, ¿e Block posiada getSprite() zwracaj¹c¹ sf::Sprite w klasie Block
}

bool Player::isMovingDown() const {
    return velocityY > 0.0f;
}

void Player::updatePosition(float deltaTime) {
    sprite.move(velocityX * deltaTime, velocityY * deltaTime);

    velocityY += gravity * deltaTime;

    if (sprite.getPosition().y >= 480.0f) {
        sprite.setPosition(sprite.getPosition().x, 480.0f);
        velocityY = 0.0f;
        isJumping = false;
        onGround = true;
    }

    // Zatrzymaj postaæ, gdy nie wykonuje skoku i przestaje poruszaæ siê w bok
    if (!isJumping && velocityX != 0.0f) {
        velocityX *= 0.98f;  // Zastosuj wspó³czynnik tarcia mniejszy ni¿ 1.0
    }

    // Zmieniamy kierunek ruchu, gdy postaæ dotyka lewej lub prawej krawêdzi ekranu
    if ((sprite.getPosition().x < 0.0f && velocityX < 0.0f) || (sprite.getPosition().x > screenWidth && velocityX > 0.0f)) {
        velocityX = -velocityX;
    }
}
