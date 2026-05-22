#include <SFML/Graphics.hpp>

int main() {
    // Creamos la ventana del juego
    sf::RenderWindow window(sf::VideoMode(800, 600), "Juego Dungeon - Test SFML");

    // Creamos un circulo verde para probar los graficos
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(300.f, 200.f);

    // Bucle principal del juego
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}