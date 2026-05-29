#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Colisionable.h"
#include "map.h"
#include "menu.h"
#include "Personaje.h"
#include "Mascota.h"
#include "Camara.h"
#include "Niebla.h"
#include "Enemy.h"
#include "ItemManager.h"    // 🌟 Nuevo: La fábrica de ítems
#include "ObjectsManager.h" // 🌟 Nuevo: Para manejar el mapa

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
	Enemy _golem;

    // 🌟 NUEVOS ATRIBUTOS: Tus dos nuevos motores de objetos
    ItemManager _itemManager;
    ObjectsManager _objectsManager;

    // 🔹 Elementos para pantalla de créditos
    sf::Font _fontCreditos;   // Fuente del texto
    sf::Text _textoCreditos;  // Texto a mostrar

    // Métodos del Game Loop
    void procesarEventos();
    void actualizar();
    void renderizar();
   
	// Funcion intermediaria para spawnear un ítem de forma segura (sin colisionar con el personaje, mapa u otros objetos)
    void spawnearDropSeguro(Item* item, sf::Texture& textura, float x, float y);

    sf::Music _musicaAmbiente;

public:
    GameManager();
    void run();
};