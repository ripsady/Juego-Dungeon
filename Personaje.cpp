#include "Personaje.h"

// Constructor: prepara el personaje antes de que empiece el juego
Personaje::Personaje() {

    /// CARGA DE TEXTURAS DEL PERSONAJE:

    // La textura es el archivo PNG cargado en memoria (la imagen cruda)
    // El sprite toma esa textura y la muestra en pantalla en una posición
    // Sin conectarlos, el sprite no sabe qué imagen dibujar
    if (!textura_abajo.loadFromFile("assets/Walk_Down-Sheet.png")) {
        return;
    }
    if (!textura_arriba.loadFromFile("assets/Walk_Up-Sheet.png")) {
        return;
    }

    // La textura de izquierda y derecha es la misma imagen
    // Para la izquierda la espejamos con setScale(-1, 1) más adelante
    if (!textura_derecha.loadFromFile("assets/Walk_Side-Sheet.png")) {
        return;
    }
    if (!textura_izquierda.loadFromFile("assets/Walk_Side-Sheet.png")) {
        return;
    }

    // Por defecto el personaje mira hacia abajo al iniciar
    sprite_del_personaje.setTexture(textura_abajo);

    // setTextureRect le dice al sprite qué parte de la imagen mostrar
    // El spritesheet tiene 6 frames juntos en una sola imagen de 384x64 píxeles
    // IntRect(x, y, ancho, alto) define el rectángulo a recortar
    // Con (0, 0, 64, 64) mostramos solo el primer frame: desde el píxel 0 hasta el 64
    sprite_del_personaje.setTextureRect(sf::IntRect(0, 0, 64, 64));

    // Coloca el personaje en la posición inicial
    sprite_del_personaje.setPosition(100.f, 100.f);

    // Define cuántos píxeles avanza el personaje por cada frame
    velocidad = 2.f;
}

// Lee las teclas W, A, S, D, cambia la textura según la dirección y mueve el personaje
void Personaje::manejarInput(Map& mapa) {

    // 1. Obtenemos la posición actual
    sf::Vector2f posActual = sprite_del_personaje.getPosition();

    // 2. NUEVA LÓGICA DE HITBOX (16x16)
    // Centramos la caja de 16px en la base del personaje (donde están los pies)
    // Asumimos que el personaje visual está en (posActual.x, posActual.y)
    // Offset X: (64 - 16) / 2 = 24. Esto centra la caja de 16px en el ancho del sprite de 64px
    // Offset Y: 48. Esto posiciona la caja en la parte inferior (pies)

    float hitBoxX = posActual.x + 24.f;
    float hitBoxY = posActual.y + 24.f;


    // W - Arriba
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (!mapa.hayColision(hitBoxX, hitBoxY - velocidad)) {
            sprite_del_personaje.move(0, -velocidad);
        }
        sprite_del_personaje.setTexture(textura_arriba);
    }

    // S - Abajo (Chequeamos el borde inferior de la caja de 16px: hitBoxY + 16)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (!mapa.hayColision(hitBoxX, hitBoxY + 16.f + velocidad)) {
            sprite_del_personaje.move(0, velocidad);
        }
        sprite_del_personaje.setTexture(textura_abajo);
    }

    // D - Derecha (Chequeamos el borde derecho de la caja de 16px: hitBoxX + 16)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (!mapa.hayColision(hitBoxX + 16.f + velocidad, hitBoxY)) {
            sprite_del_personaje.move(velocidad, 0);
        }
        sprite_del_personaje.setTexture(textura_derecha);
        sprite_del_personaje.setScale(1.f, 1.f);
        sprite_del_personaje.setOrigin(0, 0);
    }

    // A - Izquierda
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (!mapa.hayColision(hitBoxX - velocidad, hitBoxY)) {
            sprite_del_personaje.move(-velocidad, 0);
        }
        sprite_del_personaje.setTexture(textura_izquierda);
        sprite_del_personaje.setScale(-1.f, 1.f);
        sprite_del_personaje.setOrigin(64, 0);
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