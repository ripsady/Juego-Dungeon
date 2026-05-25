#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "Mascota.h"

int main() {
    // Crea la ventana donde se va a dibujar el juego
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Juego Dungeon");

    // Limita a 60 frames por segundo para que el movimiento del personaje sea consistente y no salga disparado
    ventana.setFramerateLimit(60);

    // Crea el objeto personaje (llama automáticamente al constructor de Personaje)
    Personaje personaje;

    // Crea el objeto mascota (llama automáticamente al constructor de Mascota)
    Mascota mascota;

    // Bucle principal: se repite 60 veces por segundo mientras la ventana esté abierta
    while (ventana.isOpen()) {
        sf::Event evento;

        // Revisa si ocurrió algún evento (tecla, mouse, cerrar ventana, etc.)
        while (ventana.pollEvent(evento)) {
            // Si el jugador cierra la ventana, termina el bucle
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }
     
        // Lee el teclado y mueve el personaje según la tecla presionada
        personaje.manejarInput();

        // Calcula y actualiza la posición de la mascota para que siga al personaje
        mascota.seguir(personaje.getPosicion());

        // Borra lo dibujado en el frame anterior para empezar limpio
        ventana.clear();

        // Dibuja el personaje en su posición actual
        personaje.dibujar(ventana);

        // Dibuja la mascota en su posición actual
        mascota.dibujar(ventana);

        // Muestra en pantalla todo lo que se dibujó en este frame
        ventana.display();
    }

    return 0;
}