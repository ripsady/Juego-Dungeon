#pragma once
#include <SFML/Graphics.hpp>

// Clase que representa a la mascota que sigue al personaje automáticamente
class Mascota {
private:
    sf::Sprite sprite_mascota;      // Objeto que muestra la imagen de la mascota en pantalla
    sf::Texture textura_mascota;    // Imagen cargada en memoria que usa el sprite
    float velocidad = 0.f;         // Cuántos píxeles se mueve por frame, empieza en 0
    float distancia_minima = 0.f;  // A partir de qué distancia la mascota deja de seguir al personaje

public:
    // Constructor: se ejecuta automáticamente al crear el objeto Mascota
    Mascota();

    // Calcula hacia dónde moverse para seguir al personaje
    void seguir(sf::Vector2f posicion_del_personaje);

    // Dibuja la mascota en la ventana
    void dibujar(sf::RenderWindow& ventana);
};