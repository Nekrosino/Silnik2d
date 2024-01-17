// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(const std::string& windowTitle, int screenWidth, int screenHeight);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void moveLeft();
    void moveRight();
    void jump();
    void moveUp();
    sf::FloatRect getBoundingBox() const;

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
