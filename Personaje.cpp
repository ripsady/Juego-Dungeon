#include "Personaje.h"

// Constructor: prepara el personaje antes de que empiece el juego
Personaje::Personaje() {
    // Intenta cargar la imagen del archivo, si no existe no dibuja nada
    if (!textura_del_personaje.loadFromFile("sonic2.png")) {
        return;
    }

    // Conecta la imagen cargada al sprite para que sepa qué dibujar en pantalla
    sprite_del_personaje.setTexture(textura_del_personaje);

    // Coloca el personaje en la posición inicial (100 píxeles desde la izquierda, 100 desde arriba)
    sprite_del_personaje.setPosition(100.f, 100.f);

    // Define cuántos píxeles avanza el personaje por cada frame
    velocidad = 3.f;
}

// Lee las teclas W, A, S, D y mueve el personaje en la dirección correspondiente
void Personaje::manejarInput() {
    // W mueve hacia arriba: se resta Y porque en SFML el eje Y crece hacia abajo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        sprite_del_personaje.move(0, -velocidad);
    }

    // S mueve hacia abajo: se suma Y porque en SFML el eje Y crece hacia abajo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sprite_del_personaje.move(0, velocidad);
    }

    // A mueve hacia la izquierda: se resta X porque el eje X crece hacia la derecha
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite_del_personaje.move(-velocidad, 0);
    }

    // D mueve hacia la derecha: se suma X porque el eje X crece hacia la derecha
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite_del_personaje.move(velocidad, 0);
    }
}

// Devuelve la posición actual del personaje como par de coordenadas X e Y
sf::Vector2f Personaje::getPosicion() {
    return sprite_del_personaje.getPosition();
}

// Dibuja el sprite del personaje en la ventana
void Personaje::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(sprite_del_personaje);
}