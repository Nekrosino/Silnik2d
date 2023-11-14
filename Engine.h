#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Primitives.h"
#include "Player.h"

using namespace sf;
using namespace std;

class Engine {


public:
    Engine(int screenWidth, int screenHeight, const string& windowTitle); //konstruktor
    void run(int targetFPS);
    void update(float deltaTime);
    void render();
    void setFrameRate(int targetFPS);

private:
    RenderWindow window;
    bool isFullscreen = false;
    Clock clock;
    float frameTime = 1.0f / 60.0f; // Domyœlny czas trwania jednej klatki (1/60 sekundy)
    Font font;
    Text fpsText;
    Primitives primitives;
    Player player;
    
};

#endif