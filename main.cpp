#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine.h"
#include "Primitives.h"



int main() {
    srand(time(0));
    Engine engine(800, 600, "Icy Tower");
    engine.run(60); // Uruchom gr� z 60 FPS
    return 0;
}