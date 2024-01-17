#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine.h"
#include "Primitives.h"



int main() {
    Engine engine(800, 600, "Icy Tower");
    // Inicjalizacja generatora liczb pseudolosowych
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    engine.run(60); // Uruchom grê z 60 FPS
    return 0;
}