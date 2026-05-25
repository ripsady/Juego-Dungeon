#include "Mascota.h"
#include <cmath>

// Constructor: prepara la mascota antes de que empiece el juego
Mascota::Mascota() {
    // Intenta cargar la imagen del archivo, si no existe no dibuja nada
    if (!textura_mascota.loadFromFile("sonic2.png")) {
        return;
    }

    // Conecta la imagen cargada al sprite para que sepa qué dibujar en pantalla
    sprite_mascota.setTexture(textura_mascota);

    // Coloca la mascota al lado del personaje en la posición inicial
    sprite_mascota.setPosition(200.f, 100.f);

    // Define cuántos píxeles avanza la mascota por frame (más lento que el personaje)
    velocidad = 2.f;

    // Define a cuántos píxeles de distancia la mascota deja de moverse
    distancia_minima = 80.f;
}

// Mueve la mascota hacia el personaje si está más lejos que la distancia mínima
void Mascota::seguir(sf::Vector2f posicion_del_personaje) {
    // Obtiene dónde está la mascota ahora mismo
    sf::Vector2f posicion_mascota = sprite_mascota.getPosition();

    // Calcula cuántos píxeles separan a la mascota del personaje en X e Y
    float diferencia_x = posicion_del_personaje.x - posicion_mascota.x;
    float diferencia_y = posicion_del_personaje.y - posicion_mascota.y;

    // Calcula la distancia real entre ambos usando el teorema de Pitágoras (a²+b²=c²)
    float distancia_real = std::sqrt(diferencia_x * diferencia_x + diferencia_y * diferencia_y);

    // Si la mascota está más cerca que la distancia mínima, no se mueve
    if (distancia_real > distancia_minima) {
        // Divide la diferencia por la distancia para obtener una dirección de longitud 1
        // Esto asegura que siempre se mueva a la misma velocidad sin importar el ángulo
        float direccion_x = diferencia_x / distancia_real;
        float direccion_y = diferencia_y / distancia_real;

        // Mueve la mascota en la dirección del personaje a la velocidad definida
        sprite_mascota.move(direccion_x * velocidad, direccion_y * velocidad);
    }
}

// Dibuja el sprite de la mascota en la ventana
void Mascota::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(sprite_mascota);
}