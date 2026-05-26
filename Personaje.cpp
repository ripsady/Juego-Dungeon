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
    velocidad = 1.f;
}

// Lee las teclas W, A, S, D, cambia la textura según la dirección y mueve el personaje
void Personaje::manejarInput() {

    // W mueve hacia arriba y cambia la textura para que mire hacia arriba
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        sprite_del_personaje.move(0, -velocidad);
        // Cambia la imagen del sprite a la textura de caminar hacia arriba
        sprite_del_personaje.setTexture(textura_arriba);
        // Muestra el primer frame de esa textura (el recorte de 64x64 desde el inicio)
        sprite_del_personaje.setTextureRect(sf::IntRect(0, 0, 64, 64));
        // Restaura la escala normal por si venía espejado de moverse hacia la izquierda
        sprite_del_personaje.setScale(1.f, 1.f);
        // Restaura el origen al punto inicial del sprite (esquina superior izquierda)
        sprite_del_personaje.setOrigin(0, 0);
    }

    // S mueve hacia abajo y cambia la textura para que mire hacia abajo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sprite_del_personaje.move(0, velocidad);
        // Cambia la imagen del sprite a la textura de caminar hacia abajo
        sprite_del_personaje.setTexture(textura_abajo);
        // Muestra el primer frame de esa textura
        sprite_del_personaje.setTextureRect(sf::IntRect(0, 0, 64, 64));
        // Restaura la escala normal por si venía espejado de moverse hacia la izquierda
        sprite_del_personaje.setScale(1.f, 1.f);
        // Restaura el origen al punto inicial del sprite
        sprite_del_personaje.setOrigin(0, 0);
    }

    // D mueve hacia la derecha y cambia la textura para que mire a la derecha
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite_del_personaje.move(velocidad, 0);
        // Cambia la imagen del sprite a la textura de caminar hacia la derecha
        sprite_del_personaje.setTexture(textura_derecha);
        // Muestra el primer frame de esa textura
        sprite_del_personaje.setTextureRect(sf::IntRect(0, 0, 64, 64));
        // Restaura la escala normal por si venía espejado de moverse hacia la izquierda
        sprite_del_personaje.setScale(1.f, 1.f);
        // Restaura el origen al punto inicial del sprite
        sprite_del_personaje.setOrigin(0, 0);
    }

    // A mueve hacia la izquierda y espeja la textura de lado para que mire a la izquierda
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite_del_personaje.move(-velocidad, 0);
        // Cambia la imagen del sprite a la textura de caminar hacia el lado
        sprite_del_personaje.setTexture(textura_izquierda);
        // Muestra el primer frame de esa textura
        sprite_del_personaje.setTextureRect(sf::IntRect(0, 0, 64, 64));
        // setScale(-1, 1) espeja el sprite horizontalmente para que mire a la izquierda
        // El -1 invierte el eje X (como ver la imagen en un espejo)
        // El 1 deja el eje Y sin cambios
        sprite_del_personaje.setScale(-1.f, 1.f);
        // Cuando se espeja el sprite, SFML dibuja desde el origen hacia la izquierda
        // Si el origen queda en 0, el sprite se dibuja fuera de pantalla
        // Mover el origen al borde derecho (64 píxeles) corrige eso
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