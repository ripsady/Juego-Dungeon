#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"

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

