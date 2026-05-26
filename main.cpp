#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include "menu.h"
#include "Personaje.h"
#include "Mascota.h"

using namespace std;

// =========================================
// MÁQUINA DE ESTADOS
// Define en qué pantalla se encuentra el juego
// =========================================
enum GameState {
    MENU,
    JUGANDO
};

int main() {
    // =========================================
    // 1. INICIALIZACIÓN DE VENTANA Y ESTADO
    // =========================================
    sf::RenderWindow ventana(sf::VideoMode(960, 640), "Daetherial - UTN");
    // Limita a 60 frames por segundo para que el movimiento del personaje sea consistente y no salga disparado
    ventana.setFramerateLimit(60);

    // El juego arranca siempre en el menú principal
    GameState estado = MENU;

    // =========================================
    // 2. CREACIÓN DE OBJETOS
    // =========================================

    // Crea el menú principal con el ancho y alto de la ventana
    Menu menu(960, 640);

    // Crea el mapa con tamaño de tile 32 píxeles y escala 1 (se verá el doble de grande)
    Map mapa(16, 1.0f);

    // Carga el mapa y verifica si cargó correctamente
    if (!mapa.cargarMapa("assets/collisions_mapa_v1_background.csv", "assets/mapa_v1_background.png")) {
        cout << "No se pudo cargar el mapa. Cerrando el juego." << endl;
        return -1;
    }

    // 🎥 CREACIÓN DE LA CÁMARA: Un "lente" del tamaño de nuestra ventana
    sf::View camara(sf::FloatRect(0.f, 0.f, 960.f, 640.f));

    // Crea el objeto personaje (llama automáticamente al constructor de Personaje)
    Personaje personaje;

    // Crea el objeto mascota (llama automáticamente al constructor de Mascota)
    Mascota mascota;

    // =========================================
    // 3. BUCLE PRINCIPAL DEL JUEGO
    // Se repite 60 veces por segundo mientras la ventana esté abierta
    // =========================================
    while (ventana.isOpen()) {
        sf::Event evento;

        // Revisa si ocurrió algún evento (tecla, mouse, cerrar ventana, etc.)
        while (ventana.pollEvent(evento)) {

            // Si el jugador cierra la ventana, termina el bucle
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }

            // =========================
            // INPUT SEGÚN ESTADO
            // =========================
            if (estado == MENU) {
                if (evento.type == sf::Event::KeyPressed) {

                    // Flecha arriba mueve la selección del menú hacia arriba
                    if (evento.key.code == sf::Keyboard::Up) {
                        menu.moveUp();
                    }

                    // Flecha abajo mueve la selección del menú hacia abajo
                    if (evento.key.code == sf::Keyboard::Down) {
                        menu.moveDown();
                    }

                    // Enter confirma la opción seleccionada
                    if (evento.key.code == sf::Keyboard::Enter) {
                        int selected = menu.getSelectedIndex();

                        // Si seleccionó "Inicio", pasa al estado de juego
                        if (selected == 0) {
                            estado = JUGANDO;
                        }

                        // Si seleccionó "Salir", cierra el juego
                        if (selected == 4) {
                            ventana.close();
                        }
                    }
                }
            }
        }

        // =========================
        // LÓGICA SEGÚN ESTADO
        // =========================
        if (estado == JUGANDO) {
            // 🎥 Mueve la cámara para que el personaje siempre esté en el centro
            camara.setCenter(personaje.getPosicion());

            // Lee el teclado y mueve el personaje según la tecla presionada
            personaje.manejarInput(mapa);

            // La mascota sigue automáticamente al personaje
            mascota.seguir(personaje.getPosicion());
        }

        // =========================
        // RENDER SEGÚN ESTADO
        // =========================

        // Borra lo dibujado en el frame anterior para empezar limpio
        ventana.clear(sf::Color(30, 30, 30));

        if (estado == MENU) {
            // 🚨 ANCLAJE DE INTERFAZ: Usamos la vista estática original para que el menú no se mueva
            ventana.setView(ventana.getDefaultView());

            // Dibuja la interfaz del menú principal
            menu.draw(ventana);
        }
        else if (estado == JUGANDO) {
            // 🎥 APLICAMOS LA CÁMARA: Todo lo que se dibuje de acá en adelante se ve por el lente
            ventana.setView(camara);

            // Dibuja el mapa primero para que quede detrás del personaje
            mapa.dibujarMapa(ventana);

            // DEBUG! Dibuja la capa de colisión encima del mapa
            // Esto te permite ver si los cuadros rojos coinciden con las paredes reales
            mapa.dibujarDebug(ventana);

            // Dibuja el personaje encima del mapa
            personaje.dibujar(ventana);

            // Dibuja la mascota encima del mapa
            mascota.dibujar(ventana);
        }

        // Muestra en pantalla todo lo que se dibujó en este frame
        ventana.display();
    }

    return 0;
}