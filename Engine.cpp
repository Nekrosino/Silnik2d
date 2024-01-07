// Engine.cpp
#include "Engine.h"
#include <iostream>

using namespace sf;
using namespace std;

Engine::Engine(int screenWidth, int screenHeight, const string& windowTitle)
    : primitives(), player(windowTitle, screenWidth, screenHeight), isFullscreen(false)
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
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed) {
                handleKeyPress(event.key.code);
            }
            else if (event.type == Event::KeyReleased) {
                handleKeyRelease(event.key.code);
            }
        }

        Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

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

    // Aktualizacja sterowania postaci¹
    player.update(deltaTime);
}

void Engine::render()
{
    window.clear();
    player.render(window);  // Wywo³anie funkcji render() dla obiektu klasy Player
    window.draw(fpsText);
    window.display();
}

// Dodaj implementacje funkcji handleKeyPress i handleKeyRelease
void Engine::handleKeyPress(Keyboard::Key key)
{
    // Obs³uga naciœniêcia klawisza
    switch (key)
    {
    case Keyboard::Left:
        player.moveLeft();
        break;
    case Keyboard::Right:
        player.moveRight();
        break;
    case Keyboard::Up:
        player.jump();
        break;
    default:
        break;
    }
}

void Engine::handleKeyRelease(Keyboard::Key key)
{
    // Obs³uga zwolnienia klawisza
    // Mo¿esz dodaæ dodatkow¹ logikê, jeœli potrzebujesz obs³ugi zwolnienia klawisza
}
