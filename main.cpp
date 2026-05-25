/*
	#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include "menu.h"

using namespace std;


int main() {
	// 1. Creamos la ventana del juego con SFML
	// Creamos una ventana de 800x600 píxeles con el título "Dungeon Crawler - UTN"
	sf::RenderWindow ventana(sf::VideoMode(960, 640), "Dungeon Crawler - UTN");
	ventana.setFramerateLimit(60); // Limitamos a 60 FPS para que el juego no consuma recursos innecesarios

	// 2. Creamos el mapa del juego
	Map mapa(16, 2.0f); // Creamos un objeto de la clase Map con tiles de 16x16 píxeles escalados al doble (32x32)

	// Intentamos cargar el mapa desde un archivo CSV y su correspondiente imagen de tileset
	if (!mapa.cargarMapa("assets/mapa_v1.csv", "assets/Dungeon_Tileset.png")) {
		cout << "No se pudo cargar el mapa. Cerrando el juego." << endl;
		return -1; // Salimos del programa con un código de error
	}

	// 3 . Bucle principal del juego
	while (ventana.isOpen()) {

		// --- PARTE A: PROCESAR EVENTOS (Teclado, mouse, cerrar ventana) ---
		sf::Event evento;
		while (ventana.pollEvent(evento)) {
			// Si el jugador toca la "X" de la ventana, la cerramos
			if (evento.type == sf::Event::Closed) {
				ventana.close();
			}
		}
		// --- PARTE B: ACTUALIZAR LÓGICA (Acá irá el movimiento del personaje más adelante) ---

		// --- PARTE C: DIBUJAR TODO EN PANTALLA ---
		ventana.clear(sf::Color(30, 30, 30)); // Limpiamos el fotograma anterior con un fondo gris oscuro

		mapa.dibujarMapa(ventana); // ¡PUM! Llamamos a tu pintor para que estampe la mazmorra

		ventana.display(); // Mostramos el resultado final en la pantalla del jugador
	}

	return 0; // Si salimos del bucle, el juego termina limpiamente
} // Fin del main

*/













#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include "menu.h"

using namespace std;

enum GameState {
    MENU,
    JUGANDO
};

int main() {
    sf::RenderWindow ventana(sf::VideoMode(960, 640), "Dungeon Crawler - UTN");
    ventana.setFramerateLimit(60);

    // 🔹 Crear menú
    Menu menu(960, 640);

    // 🔹 Estado inicial
    GameState estado = MENU;

    // 🔹 Crear mapa
    Map mapa(16, 2.0f);

    if (!mapa.cargarMapa("assets/mapa_v1.csv", "assets/Dungeon_Tileset.png")) {
        cout << "No se pudo cargar el mapa. Cerrando el juego." << endl;
        return -1;
    }

    while (ventana.isOpen()) {
        sf::Event evento;

        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                ventana.close();

            // =========================
            // 🎮 INPUT SEGÚN ESTADO
            // =========================

            if (estado == MENU) {
                if (evento.type == sf::Event::KeyPressed) {

                    if (evento.key.code == sf::Keyboard::Up)
                        menu.moveUp();

                    if (evento.key.code == sf::Keyboard::Down)
                        menu.moveDown();

                    if (evento.key.code == sf::Keyboard::Enter) {
                        int selected = menu.getSelectedIndex();

                        if (selected == 0) {
                            estado = JUGANDO; // 👉 Entrás al juego
                        }

                        if (selected == 4) {
                            ventana.close();
                        }
                    }
                }
            }

            else if (estado == JUGANDO) {
                // 👉 Acá después vas a manejar movimiento del player
            }
        }

        // =========================
        // 🎨 RENDER SEGÚN ESTADO
        // =========================

        ventana.clear(sf::Color(30, 30, 30));

        if (estado == MENU) {
            menu.draw(ventana);
        }
        else if (estado == JUGANDO) {
            mapa.dibujarMapa(ventana);
        }

        ventana.display();
    }

    return 0;
}