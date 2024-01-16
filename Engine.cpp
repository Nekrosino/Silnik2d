// Engine.cpp

#include "Engine.h"
#include <iostream>

Engine::Engine(int screenWidth, int screenHeight, const std::string& windowTitle)
    : player(windowTitle, screenWidth, screenHeight), isFullscreen(false), blockSpawnInterval(2.0f)
{
    window.create(sf::VideoMode(screenWidth, screenHeight), windowTitle);

    if (!font.loadFromFile("fonts/ARCADECLASSIC.ttf")) {
        std::cerr << "Nie mo�na za�adowa� czcionki" << std::endl;
    }

    fpsText.setFont(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10, 10);
}

void Engine::run(int targetFPS) {
    window.setFramerateLimit(targetFPS);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                handleKeyPress(event.key.code);
            }
            else if (event.type == sf::Event::KeyReleased) {
                handleKeyRelease(event.key.code);
            }
        }

        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        // Aktualizacja i renderowanie gry z uwzgl�dnieniem deltaTime
        update(deltaTime);
        render();

        float fps = 1.0f / elapsed.asSeconds();
        fpsText.setString("FPS " + std::to_string(static_cast<int>(fps)));
    }
}

void Engine::update(float deltaTime) {
    // Aktualizacja sterowania postaci� tylko je�li nie koliduje z blokami
    if (!isPlayerCollidingWithBlocks()) {
        player.update(deltaTime);
    }

    // Aktualizacja blok�w
    for (auto& block : blocks) {
        block.update(deltaTime);
    }

    // Sprawdzenie kolizji
    if (isPlayerCollidingWithBlocks()) {
        // Obs�uga kolizji, na przyk�ad zatrzymanie postaci
        player.moveLeft();
    }

    // Usuwanie blok�w, kt�re opad�y poza ekran
    blocks.erase(std::remove_if(blocks.begin(), blocks.end(),
        [](const Block& block) { return block.getY() > 600; }),
        blocks.end());

    // Dodawanie nowych blok�w z okre�lonym interwa�em
    if (blockSpawnClock.getElapsedTime().asSeconds() >= blockSpawnInterval) {
        float randomX = static_cast<float>(rand() % (700));
        Block block(randomX, 0.0f, 50.0f, 20.0f, "textures/ice.png");
        blocks.push_back(block);
        blockSpawnClock.restart();  // Zresetuj zegar po stworzeniu bloku
    }
}

void Engine::render() {
    window.clear();

    // Renderowanie blok�w
    for (const auto& block : blocks) {
        block.render(window);
    }

    // Renderowanie postaci
    player.render(window);

    // Renderowanie tekstu FPS
    window.draw(fpsText);

    window.display();
}

void Engine::handleKeyPress(sf::Keyboard::Key key) {
    // Obs�uga naci�ni�cia klawisza
    switch (key) {
    case sf::Keyboard::Left:
        player.moveLeft();
        break;
    case sf::Keyboard::Right:
        player.moveRight();
        break;
    case sf::Keyboard::Up:
        player.jump();
        break;
    default:
        break;
    }
}

void Engine::handleKeyRelease(sf::Keyboard::Key key) {
    // Obs�uga zwolnienia klawisza
    // Mo�esz doda� dodatkow� logik�, je�li potrzebujesz obs�ugi zwolnienia klawisza
}

bool Engine::isPlayerCollidingWithBlocks() {
    for (const auto& block : blocks) {
        // Sprawdzamy, czy prostok�t postaci przecina si� z prostok�tem bloku
        if (player.getX() < block.getX() + block.getWidth() &&
            player.getX() + player.getWidth() > block.getX() &&
            player.getY() < block.getY() + block.getHeight() &&
            player.getY() + player.getHeight() > block.getY()) {
            return true;  // Koliduje
        }
    }
    return false;  // Nie koliduje
}
