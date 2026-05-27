#include "GameManager.h"
#include <iostream>
using namespace std;

// Constructor: Inicializa la ventana y los objetos con el nuevo nombre
GameManager::GameManager()
    : _ventana(sf::VideoMode(960, 640), "Daetherial - UTN"),
	_camara(960.f, 640.f), // Inicializa la cámara con el tamaño de la ventana
    _estado(MENU),
    _menu(960, 640),
    _mapa(16, 1.0f)
{
    _ventana.setFramerateLimit(60);

    // Carga del mapa base
    if (!_mapa.cargarMapa("assets/collisions_mapa_v1_background.csv", "assets/mapa_v1_background.png")) {
        cout << "❌ No se pudo cargar el mapa. Cerrando el juego." << endl;
        _ventana.close();
    }
}

// Bucle principal del juego
void GameManager::run() {
    while (_ventana.isOpen()) {
        procesarEventos();
        actualizar();
        renderizar();
    }
}

// 1. Gestión de Inputs y Eventos
void GameManager::procesarEventos() {
    sf::Event evento;
    while (_ventana.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            _ventana.close();
        }

        // 🌟 LA LÍNEA CLAVE: El mánager atrapa el evento del mouse y se lo pasa a la cámara
        if (_estado == JUGANDO) {
            _camara.procesarZoom(evento);
        }


        // Lógica de entrada del MENÚ
        if (_estado == MENU) {
            if (evento.type == sf::Event::KeyPressed) {
                if (evento.key.code == sf::Keyboard::Up) {
                    _menu.moveUp();
                }
                if (evento.key.code == sf::Keyboard::Down) {
                    _menu.moveDown();
                }
                if (evento.key.code == sf::Keyboard::Enter) {
                    int selected = _menu.getSelectedIndex();

                    if (selected == 0) {
                        _estado = JUGANDO;
                    }
                    else if (selected == 1) {
                        _estado = CREDITOS;
                    }
                    else if (selected == 4) {
                        _ventana.close();
                    }
                }
            }
        }
        // Lógica de entrada de los CRÉDITOS
        else if (_estado == CREDITOS) {
            if (evento.type == sf::Event::KeyPressed) {
                if (evento.key.code == sf::Keyboard::Escape) {
                    _estado = MENU;
                }
            }
        }
    }
}

// 2. Actualización de físicas y posiciones
void GameManager::actualizar() {
    if (_estado == JUGANDO) {
        _camara.seguir(_personaje.getPosicion());
        _personaje.manejarInput(_mapa);
        _mascota.seguir(_personaje.getPosicion());
    }
}

// 3. Dibujo en pantalla
void GameManager::renderizar() {
    _ventana.clear(sf::Color(30, 30, 30));

    if (_estado == MENU) {
        _ventana.setView(_ventana.getDefaultView());
        _menu.draw(_ventana);
    }
    else if (_estado == JUGANDO) {
        _ventana.setView(_camara.getVista());

        // 1. Dibujamos el fondo del mapa primero
        _mapa.dibujarMapa(_ventana);

        // 🌟 ¡ACÁ VA TU FUNCIÓN! 
        // Como estás dentro de GameManager, usás tus variables miembro: _mapa y _ventana
        _mapa.dibujarDebug(_ventana);

        // 3. Dibujamos los personajes encima de todo para que no los tapen los cuadrados
        _personaje.dibujar(_ventana);
        _mascota.dibujar(_ventana);


    }
    else if (_estado == CREDITOS) {
        _ventana.setView(_ventana.getDefaultView());
        // Pantalla lista para los textos de créditos
    }

    _ventana.display();
}

