// Engine.cpp
#include "Engine.h"
#include <iostream>

using namespace sf;
using namespace std;

Engine::Engine(int screenWidth, int screenHeight, const string& windowTitle)
    : primitives(), player(windowTitle, screenWidth, screenHeight), isFullscreen(false), blockSpawnInterval(2.0f) // Inicjalizacja blockSpawnInterval
{
    window.create(VideoMode(screenWidth, screenHeight), windowTitle);

    if (!font.loadFromFile("fonts/ARCADECLASSIC.ttf"))
    {
        cerr << "Nie mozna zaladowac czcionki" << endl;
    }

        if (!font.loadFromFile("fonts/ARCADECLASSIC.ttf")) {
        cerr << "Nie mozna zaladowac czcionki" << endl;
    }

        // £adowanie tekstury bloków
        if (!blockTexture.loadFromFile("textures/ice.png")) {
            cerr << "B³¹d ³adowania tekstury bloków" << endl;
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

    if (Keyboard::isKeyPressed(Keyboard::B)) {
        blocks.emplace_back(100.0f, 100.0f, 50.0f, 20.0f, blockTexture);
    }

    int maxLiczbaBlokow = 4;
    int liczbaUtworzonychBlokow = 0;

    if (blockSpawnClock.getElapsedTime().asSeconds() >= blockSpawnInterval && liczbaUtworzonychBlokow < maxLiczbaBlokow) {
        float randomX = static_cast<float>(rand() % 400 + 100);
        blocks.emplace_back(randomX, 0.0f, 50.0f, 20.0f, blockTexture);
        liczbaUtworzonychBlokow++;
        blockSpawnClock.restart();
    }

    blocks.erase(std::remove_if(blocks.begin(), blocks.end(),
        [](const Block& block) { return block.getY() >= 600; }),
        blocks.end());

    for (auto& block : blocks) {
        block.moveDown(5.0f);
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

    player.update(deltaTime);

    for (auto& block : blocks) {
        if (player.isCollidingWith(block)) {
            if (player.isMovingDown()) {
                player.bounceUp();
            }
            // Dodaj inne dzia³ania zwi¹zane z kolizj¹, jeœli s¹ potrzebne
            blocks.erase(std::remove(blocks.begin(), blocks.end(), block), blocks.end());
        }
    }

    for (const auto& block : blocks) {
        block.render(window);
    }
}



void Engine::render()
{
    window.clear();
    // Renderowanie bloków
    for (const auto& block : blocks) {
        block.render(window);
    }

    window.draw(backgroundSprite);

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
