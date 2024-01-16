// Engine.h
#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Primitives.h"
#include "Player.h"
#include "Block.h"

using namespace sf;
using namespace std;

class Engine {
public:
    Engine(int screenWidth, int screenHeight, const string& windowTitle);

    void run(int targetFPS);
    void update(float deltaTime);
    void render();
    void setFrameRate(int targetFPS);

    // Dodaj deklaracje funkcji obs³ugi klawiszy
    void handleKeyPress(Keyboard::Key key);
    void handleKeyRelease(Keyboard::Key key);

private:
    RenderWindow window;
    bool isFullscreen;
    Clock clock;
    float frameTime;
    Font font;
    Text fpsText;
    Primitives primitives;
    Player player;
    std::vector<Block> blocks; // Wektor bloków
};

#endif
