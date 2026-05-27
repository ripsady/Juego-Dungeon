#pragma once
#include <SFML/Graphics.hpp>
#include "map.h"
#include "menu.h"
#include "Personaje.h"
#include "Mascota.h"
#include "Camara.h"

enum GameState {
    MENU,
    JUGANDO,
    CREDITOS
};

class GameManager {
private:
    // Componentes principales de SFML
    sf::RenderWindow _ventana;
	Camara _camara; // Cámara para seguir al personaje
    GameState _estado;

    // Objetos del juego
    Menu _menu;
    Map _mapa;
    Personaje _personaje;
    Mascota _mascota;

    // Métodos privados para las tres etapas del Game Loop
    void procesarEventos();
    void actualizar();
    void renderizar();

public:
    GameManager(); // Constructor
    void run();    // Arranca el bucle principal
};