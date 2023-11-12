
#include "Engine.h"


using namespace sf;
using namespace std;


    Engine::Engine(int screenWidth, int screenHeight, const string& windowTitle) : primitives()
    {
        window.create(VideoMode(screenWidth, screenHeight), windowTitle);

        if (!font.loadFromFile("fonts/ARCADECLASSIC.ttf"))
        {
            cerr << "Nie mozna zaladowac czcionki" << endl;
        }

        fpsText.setFont(font);
        fpsText.setCharacterSize(24);
        fpsText.setFillColor(Color::White);
        fpsText.setPosition(10, 10);
    }

    void Engine::run(int targetFPS) {
      //  setFrameRate(targetFPS); // Ustaw iloœæ klatek na sekundê
        window.setFramerateLimit(60);
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
            }
            Time elapsed = clock.restart();
            float deltaTime = elapsed.asSeconds();
           // float deltaTime = clock.restart().asSeconds();

            // Aktualizacja i renderowanie gry z uwzglêdnieniem deltaTime
            update(deltaTime);
            render();

            float fps = 1.0f / elapsed.asSeconds();
            fpsText.setString("FPS " + to_string(static_cast<int>(fps)));
        }
    }

    void Engine::update(float deltaTime)
    {   
        if (Keyboard::isKeyPressed(Keyboard::F1))
        {
            window.setFramerateLimit(30);
        }

        else if (Keyboard::isKeyPressed(Keyboard::F2))
        {
            window.setFramerateLimit(60);
        }
        else if (Keyboard::isKeyPressed(Keyboard::F3))
        {
            window.setFramerateLimit(144);
        }
        if (Keyboard::isKeyPressed(Keyboard::F))
        {
            isFullscreen = !isFullscreen;

            if (isFullscreen)
            {
                
                window.create(sf::VideoMode(1920, 1080), "Aplikacja Fullscreen", sf::Style::Fullscreen);
                window.setFramerateLimit(60);
            }
            else
            {
                window.create(sf::VideoMode(800, 600), "Icy Tower", sf::Style::Default);
                window.setFramerateLimit(60);
            }
        }
       
    }

    void Engine::render()
    {
        window.clear();

        Vector2f point1(100, 100);
        Vector2f point2(200, 200);
        primitives.drawLine(window,point1,point2);
        Vector2f circleCenter(300, 300);
        float circleRadius = 50.0f;
        primitives.drawCircle(window, circleCenter, circleRadius);

        Vector2f trianglePoint1(400, 400);
        Vector2f trianglePoint2(500, 500);
        Vector2f trianglePoint3(550, 450);
        primitives.drawTriangle(window, trianglePoint1, trianglePoint2, trianglePoint3);

        Vector2f squareTopLeft(400, 550);
        float squareSize = 80.0f;
        primitives.drawSquare(window, squareTopLeft, squareSize);
    
        window.draw(fpsText);

        window.display();
     
    }

    void Engine::setFrameRate(int targetFPS) {
        if (targetFPS <= 0) {
            // Jeœli targetFPS jest nieprawid³owy, u¿yj domyœlnego FPS (60)
            targetFPS = 60;
        }
        frameTime = 1.0f / static_cast<float>(targetFPS);
    }



