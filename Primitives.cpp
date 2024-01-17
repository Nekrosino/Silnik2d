#include "Primitives.h"
#include <iostream>
using namespace sf;


    void Primitives::drawLine(RenderWindow& window, Vector2f point1, Vector2f point2)
    {
        Vertex line[] = {
            Vertex(point1),
            Vertex(point2)
        };
        //  cout << "Rysowanie linii";
        std::cout << "Plik Primitives.cpp zostal kompilowany." << std::endl; // Dodaj ten komunikat
        window.draw(line, 2, sf::Lines);
    }

    void Primitives::drawCircle(RenderWindow& window, Vector2f center, float radius) {
        CircleShape circle(radius);
        circle.setPosition(center);
        circle.setFillColor(Color::Green);  //Kolor
        window.draw(circle);
    }

    void Primitives::drawSquare(RenderWindow& window, Vector2f topLeft, float size) {
        RectangleShape square(Vector2f(size, size));
        square.setPosition(topLeft);
        square.setFillColor(Color::White); //Kolor
        window.draw(square);
    }


    void Primitives::drawTriangle(RenderWindow& window, Vector2f point1, Vector2f point2, Vector2f point3) {
        ConvexShape triangle(3); //Ilosc wierzcholkow
        triangle.setPoint(0, point1);
        triangle.setPoint(1, point2);
        triangle.setPoint(2, point3);
        triangle.setFillColor(Color::Blue); // Kolor
        window.draw(triangle);
    }

