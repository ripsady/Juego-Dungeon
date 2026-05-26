#pragma once
#include <SFML/Graphics.hpp>

// Clase que representa al personaje controlado por el jugador
class Personaje {
private:
    sf::Sprite sprite_del_personaje;    // Objeto que muestra la imagen del personaje en pantalla
    sf::Texture textura_abajo;          // Imagen cuando mira hacia abajo
    sf::Texture textura_arriba;         // Imagen cuando mira hacia arriba
    sf::Texture textura_derecha;        // Imagen cuando mira hacia la derecha
    sf::Texture textura_izquierda;      // Imagen cuando mira hacia la izquierda
    float velocidad = 0.f;              // Cuántos píxeles se mueve por frame, empieza en 0

public:
    // Constructor: se ejecuta automáticamente al crear el objeto Personaje
    Personaje();

    // Lee el teclado y mueve el personaje según la tecla presionada
    void manejarInput();

    // Devuelve las coordenadas X e Y actuales del personaje
    sf::Vector2f getPosicion();

    // Dibuja el personaje en la ventana
    void dibujar(sf::RenderWindow& ventana);
};