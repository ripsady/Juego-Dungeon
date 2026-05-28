#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"
#include "menu.h"
#include "Personaje.h"
#include "Mascota.h"
#include "Camara.h"
#include "Niebla.h"

// Estados del juego
enum GameState {
    MENU,
    JUGANDO,
    CREDITOS
};

class GameManager {
private:
    // Ventana principal
    sf::RenderWindow _ventana;

    // Cámara
    Camara _camara;

    // Estado actual del juego
    GameState _estado;
	Niebla _niebla; // Capa de niebla para el efecto visual
	sf::Clock _reloj; // Reloj para medir el tiempo entre frames

    // Objetos del juego
    Menu _menu;
    Map _mapa;
    Personaje _personaje;
    Mascota _mascota;

    // 🔹 Elementos para pantalla de créditos
    sf::Font _fontCreditos;   // Fuente del texto
    sf::Text _textoCreditos;  // Texto a mostrar

    // Métodos del Game Loop
    void procesarEventos();
    void actualizar();
    void renderizar();

    sf::Music _musicaAmbiente;

public:
    GameManager();
    void run();
};