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

    void drawCircle(RenderWindow& window, Vector2f center, float radius) {
        CircleShape circle(radius);
        circle.setPosition(center);
        circle.setFillColor(Color::Green);  //Kolor
        window.draw(circle);
    }

    void drawSquare(RenderWindow& window, Vector2f topLeft, float size) {
        RectangleShape square(Vector2f(size, size));
        square.setPosition(topLeft);
        square.setFillColor(Color::White); //Kolor
        window.draw(square);
    }


    void drawTriangle(RenderWindow& window, Vector2f point1, Vector2f point2, Vector2f point3) {
        ConvexShape triangle(3); //Ilosc wierzcholkow
        triangle.setPoint(0, point1);
        triangle.setPoint(1, point2);
        triangle.setPoint(2, point3);
        triangle.setFillColor(Color::Blue); // Kolor
        window.draw(triangle);
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

        Vector2f circleCenter(300, 300);
        float circleRadius = 50.0f;
        primitives.drawCircle(window, circleCenter, circleRadius);

        Vector2f trianglePoint1(400, 400);
        Vector2f trianglePoint2(500, 500);
        Vector2f trianglePoint3(550, 450);
        primitives.drawTriangle(window, trianglePoint1, trianglePoint2, trianglePoint3);

        Vector2f squareTopLeft(600, 600);
        float squareSize = 80.0f;
        primitives.drawSquare(window, squareTopLeft, squareSize);

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