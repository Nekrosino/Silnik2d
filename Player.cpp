// Player.cpp

#include "Player.h"
#include <iostream>

Player::Player(const std::string& windowTitle, int screenWidth, int screenHeight)
    : velocityX(0.0f), velocityY(0.0f), isJumping(false), gravity(2000.0f), jumpHeight(300.0f), onGround(true),
    screenWidth(screenWidth)
{
    if (!texture.loadFromFile("textures/test.png")) {
        std::cerr << "Nie mo¿na za³adowaæ tekstury postaci." << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setPosition(screenWidth / 2.0f, screenHeight - sprite.getGlobalBounds().height);
}

void Player::update(float deltaTime) {
    // Aktualizacja pozycji gracza
    sprite.move(velocityX * deltaTime, velocityY * deltaTime);

    // Symulacja grawitacji
    velocityY += gravity * deltaTime;

    // Sprawdzenie czy gracz dotyka ziemi
    if (sprite.getPosition().y >= 480.0f) {
        sprite.setPosition(sprite.getPosition().x, 480.0f);
        velocityY = 0.0f;
        isJumping = false;
        onGround = true;
    }

    // Zastosowanie oporu powietrza, aby stopniowo zwalniaæ gracza po puszczeniu klawisza
    if (!isJumping && velocityX != 0.0f) {
        velocityX *= 0.95f;
    }

    // Odbijanie siê od lewej i prawej krawêdzi ekranu
    if (sprite.getPosition().x < 0.0f) {
        sprite.setPosition(0.0f, sprite.getPosition().y);
        velocityX = std::abs(velocityX); // Zmiana kierunku na dodatni
    }
    else if (sprite.getPosition().x > screenWidth - sprite.getGlobalBounds().width) {
        sprite.setPosition(screenWidth - sprite.getGlobalBounds().width, sprite.getPosition().y);
        velocityX = -std::abs(velocityX); // Zmiana kierunku na ujemny
    }
}

void Player::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::moveLeft() {
    velocityX = -300.0f;
}

void Player::moveRight() {
    velocityX = 300.0f;
}

void Player::jump() {
    // Skok jest mo¿liwy tylko jeœli gracz jest na ziemi
    if (!isJumping && onGround) {
        velocityY = -sqrt(2.0f * gravity * jumpHeight);
        isJumping = true;
        onGround = false;
    }
}

float Player::getX() const {
    return sprite.getPosition().x;
}

float Player::getY() const {
    return sprite.getPosition().y;
}

float Player::getWidth() const {
    return sprite.getGlobalBounds().width;
}

float Player::getHeight() const {
    return sprite.getGlobalBounds().height;
}

bool Player::getOnGround() const {
    return onGround;
}

bool Player::getIsJumping() const {
    return isJumping;
}
