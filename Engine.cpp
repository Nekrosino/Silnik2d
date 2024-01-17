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

        // �adowanie tekstury blok�w
        if (!blockTexture.loadFromFile("textures/ice.png")) {
            cerr << "B��d �adowania tekstury blok�w" << endl;
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

        // Aktualizacja i renderowanie gry z uwzgl�dnieniem deltaTime
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
        // blocks.emplace_back(400.0f, 400.0f, 50.0f, 20.0f, "textures/ice.png");
       //  blocks.emplace_back(400.0f, 500.0f, 50.0f, 20.0f, "textures/ice.png");
        // blocks.emplace_back(400.0f, 400.0f, 50.0f, 20.0f, "textures/ice.png");
        // blocks.emplace_back(500.0f, 0.0f, 50.0f, 20.0f, "textures/ice.png");

    }

    // Deklaracja zmiennej przechowuj�cej maksymaln� liczb� blok�w
    int maxLiczbaBlokow = 4;

    // Deklaracja zmiennej przechowuj�cej liczb� utworzonych blok�w
    int liczbaUtworzonychBlokow = 0;

    // Automatyczne tworzenie blok�w co okre�lony interwa� czasowy
    if (blockSpawnClock.getElapsedTime().asSeconds() >= blockSpawnInterval && liczbaUtworzonychBlokow < maxLiczbaBlokow) {
        float randomX = static_cast<float>(rand() % 400 + 100);  // Losowa warto�� X w przedziale 100-500
        blocks.emplace_back(randomX, 0.0f, 50.0f, 20.0f, blockTexture);
        liczbaUtworzonychBlokow++;
        blockSpawnClock.restart();  // Zresetuj zegar po stworzeniu bloku
    }

    // Usuwanie blok�w, kt�re osi�gn�y punkt Y r�wny 600
    blocks.erase(std::remove_if(blocks.begin(), blocks.end(),
        [](const Block& block) { return block.getY() >= 900; }),
        blocks.end());

    // Poruszanie blok�w w d�
    for (auto& block : blocks) {
        block.moveDown(5.0f);  // Przesu� blok w d� o 50 jednostek
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

    // Aktualizacja sterowania postaci�
    player.update(deltaTime);
    // Renderowanie blok�w
    for (const auto& block : blocks) {
        block.render(window);
    }
    checkCollisions();
}

void Engine::render()
{
    window.clear();
    // Renderowanie blok�w
    for (const auto& block : blocks) {
        block.render(window);
    }

    player.render(window);  // Wywo�anie funkcji render() dla obiektu klasy Player

    window.draw(fpsText);
    window.display();
}

// Dodaj implementacje funkcji handleKeyPress i handleKeyRelease
void Engine::handleKeyPress(Keyboard::Key key)
{
    // Obs�uga naci�ni�cia klawisza
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
    // Obs�uga zwolnienia klawisza
    // Mo�esz doda� dodatkow� logik�, je�li potrzebujesz obs�ugi zwolnienia klawisza
}


void Engine::checkCollisions() {
    sf::FloatRect playerBounds = player.getBoundingBox();

    for (auto& block : blocks) {
        sf::FloatRect blockBounds = block.getBoundingBox();

        if (playerBounds.intersects(blockBounds)) {
            // Kolizja! Tutaj mo�esz zaimplementowa� dowoln� logik� zwi�zan� z kolizj�.

            // Na przyk�ad, przesu� gracza w g�r� o pewn� warto��
            float displacement = 50.0f;

           // player.moveUp(displacement);
            player.moveUp();

            // Mo�esz tak�e zastosowa� inne efekty, np. zmniejszy� �ycie gracza, itp.
        }
    }
}