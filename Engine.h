// Engine.h

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Block.h"

class Engine {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text fpsText;
    std::vector<Block> blocks;
    Player player;
    bool isFullscreen;

    sf::Clock clock;
    sf::Clock blockSpawnClock;
    float blockSpawnInterval;

public:
    Engine(int screenWidth, int screenHeight, const std::string& windowTitle);
    void run(int targetFPS);

private:
    void update(float deltaTime);
    void render();
    void handleKeyPress(sf::Keyboard::Key key);
    void handleKeyRelease(sf::Keyboard::Key key);
    bool isPlayerCollidingWithBlocks();
};

