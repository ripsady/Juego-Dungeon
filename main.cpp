#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include "menu.h"

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
    ventana.setFramerateLimit(60); // Limitamos a 60 FPS por rendimiento

    // El juego arranca siempre en el menú principal
    GameState estado = MENU;

    // =========================================
    // 2. CREACIÓN DE OBJETOS (Menú y Mapa)
    // =========================================
    Menu menu(960, 640);

    // OJO: Tu compañero dejó (16, 2.0f). Acordate que para tu mapa va (32, 1.0f)
    Map mapa(16, 2.0f);

    // OJO: Acordate de cambiar "Dungeon_Tileset.png" por tu fondo gigante
    if (!mapa.cargarMapa("assets/mapa_v1.csv", "assets/Dungeon_Tileset.png")) {
        cout << "No se pudo cargar el mapa. Cerrando el juego." << endl;
        return -1;
    }

    // =========================================
    // 3. BUCLE PRINCIPAL DEL JUEGO
    // =========================================
    while (ventana.isOpen()) {
        sf::Event evento;

        // --- PROCESAMIENTO DE EVENTOS ---
        while (ventana.pollEvent(evento)) {

            // Si el jugador toca la "X" de la ventana, cerramos
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }

            // =========================
            // 🎮 INPUT SEGÚN ESTADO
            // =========================
            if (estado == MENU) {
                if (evento.type == sf::Event::KeyPressed) {

                    // Navegación por las opciones del menú
                    if (evento.key.code == sf::Keyboard::Up) {
                        menu.moveUp();
                    }
                    if (evento.key.code == sf::Keyboard::Down) {
                        menu.moveDown();
                    }

                    // Selección de opción con Enter
                    if (evento.key.code == sf::Keyboard::Enter) {
                        int selected = menu.getSelectedIndex();

                        if (selected == 0) {
                            estado = JUGANDO; // 👉 Transición: Entrás al juego
                        }
                        if (selected == 4) {
                            ventana.close();  // 👉 Salir del juego
                        }
                    }
                }
            }
            else if (estado == JUGANDO) {
                // 👉 Acá después vas a manejar el input de movimiento del player
            }
        }

        // =========================
        // 🎨 RENDER SEGÚN ESTADO
        // =========================

        // Limpiamos el fotograma anterior con un fondo gris oscuro
        ventana.clear(sf::Color(30, 30, 30));

        if (estado == MENU) {
            menu.draw(ventana); // Dibuja la interfaz del menú principal
        }
        else if (estado == JUGANDO) {
            mapa.dibujarMapa(ventana); // Dibuja la mazmorra / cripta
            // 👉 Acá vas a dibujar al personaje principal y la mascota
        }

        // Mostramos el resultado final en la pantalla
        ventana.display();
    }

    return 0; // Fin del main
}