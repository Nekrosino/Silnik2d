#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Primitives {
public:
    void drawLine(RenderWindow& window, Vector2f point1, Vector2f point2)
    {   
        Vertex line[] = {
            Vertex(point1),
            Vertex(point2)
        };
        cout << "Rysowanie linii";
        window.draw(line, 2, sf::Lines);
    }

};

class Engine {
private:
    RenderWindow window;
    Clock clock;
    float frameTime = 1.0f / 60.0f; // Domyœlny czas trwania jednej klatki (1/60 sekundy)
    Primitives primitives;

public:
    Engine(int screenWidth, int screenHeight, const std::string& windowTitle) {
        window.create(VideoMode(screenWidth, screenHeight), windowTitle);
    }

    void run(int targetFPS) {
        setFrameRate(targetFPS); // Ustaw iloœæ klatek na sekundê
        
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
            }

            float deltaTime = clock.restart().asSeconds();

            // Aktualizacja i renderowanie gry z uwzglêdnieniem deltaTime
            update(deltaTime);
            render();
        }
    }

    void update(float deltaTime)
    {

    }

    void render()
    {
        window.clear();

        Vector2f point1(100, 100);
        Vector2f point2(200, 200);
        primitives.drawLine(window,point1,point2);

        window.display();
    }

    void setFrameRate(int targetFPS) {
        if (targetFPS <= 0) {
            // Jeœli targetFPS jest nieprawid³owy, u¿yj domyœlnego FPS (60)
            targetFPS = 60;
        }
        frameTime = 1.0f / static_cast<float>(targetFPS);
    }

};

int main() {
    Engine engine(800, 600, "Icy Tower");
    engine.run(60); // Uruchom grê z 60 FPS
    return 0;
}