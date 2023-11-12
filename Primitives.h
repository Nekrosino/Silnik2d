#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <SFML/Graphics.hpp>
using namespace sf;
class Primitives {
public:
    void drawLine(RenderWindow& window, Vector2f point1, Vector2f point2);

    void drawCircle(RenderWindow& window, Vector2f center, float radius);

    void drawSquare(RenderWindow& window, Vector2f topLeft, float size);

    void drawTriangle(RenderWindow& window, Vector2f point1, Vector2f point2, Vector2f point3);

  

};

#endif