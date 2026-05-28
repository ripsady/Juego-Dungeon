#include "GameManager.h"
#include <iostream>
using namespace std;

// Constructor
GameManager::GameManager()
	: _ventana(sf::VideoMode(960, 640), "Daetherial - UTN"),
	  _camara(960.f, 640.f),
	  _estado(MENU),
	  _menu(960, 640),
	  _mapa(16, 1.0f),
	  _golem(sf::Vector2f(500.f, 400.f)) // Posición inicial del Gólem
{
	_ventana.setFramerateLimit(60);

    // ================= MAPA =================
    if (!_mapa.cargarMapa("assets/collisions_mapa_v1_background.csv", "assets/mapa_v1_background.png")) {
        cout << "❌ No se pudo cargar el mapa. Cerrando el juego." << endl;
        _ventana.close();
    }

	// ================= SONIDO AMBIENTE =================
	if (!_musicaAmbiente.openFromFile("assets/ambient.wav")) {
		cout << "❌ Error cargando musica de ambiente" << endl;
	}
	else {
		_musicaAmbiente.setLoop(true);
	}

    // ================= CREDITOS =================
    // Carga de fuente (IMPORTANTE verificar ruta si falla)
    if (!_fontCreditos.loadFromFile("assets/NorthEternal-yYl4V.otf")) {
        cout << "❌ Error cargando fuente de creditos" << endl;
    }

    // Configuración del texto
    _textoCreditos.setFont(_fontCreditos);
    _textoCreditos.setCharacterSize(11.5);
    _textoCreditos.setFillColor(sf::Color::White);

    // Contenido de los créditos
    _textoCreditos.setString(
        "CREDITOS\n\n"
        "Desarrollado por:\n"
        "Grupo 18 - Programacion 2\n"
        "Turno noche | Comision 102 (Virtual)\n\n"

        "Integrantes:\n"
        "- Federico Wachenschwan\n"
        "- Juan Corbacho\n"
        "- Andres Ignacio Fernandez Escudero\n"
        "- Miguel Salazar\n\n"

        "Tipo de proyecto:\n"
        "Juego\n\n"

        "Descripcion:\n"
        "Juego de supervivencia contra\n"
        "oleadas de mobs con mejoras y logros."
        "Presiona ESC para volver\n\n"

        "Para volver preciona ESC"
    );

    // Posición en pantalla
    _textoCreditos.setPosition(120, 100);
}

// Bucle principal
void GameManager::run() {
    while (_ventana.isOpen()){ 
        procesarEventos();
        actualizar();
        renderizar();
    }
}

// ================= EVENTOS =================
void GameManager::procesarEventos() {
    sf::Event evento;

    while (_ventana.pollEvent(evento)) {

        if (evento.type == sf::Event::Closed) {
            _ventana.close();
        }

        // Zoom solo en juego
        if (_estado == JUGANDO) {
            _camara.procesarZoom(evento);
        }

        // ===== MENU =====
        if (_estado == MENU) {
            if (evento.type == sf::Event::KeyPressed) {

                if (evento.key.code == sf::Keyboard::Up)
                    _menu.moveUp();

                if (evento.key.code == sf::Keyboard::Down)
                    _menu.moveDown();

                if (evento.key.code == sf::Keyboard::Enter) {
                    int selected = _menu.getSelectedIndex();

                    _musicaAmbiente.play();

                    if (selected == 0)
                        _estado = JUGANDO;

                    else if (selected == 2) // CREDITOS
                        _estado = CREDITOS;

                    else if (selected == 3)
                        _ventana.close();
                }
            }
        }

        // ===== CREDITOS =====
        else if (_estado == CREDITOS) {
            if (evento.type == sf::Event::KeyPressed) {
                if (evento.key.code == sf::Keyboard::Escape) {
                    _estado = MENU;
                }
            }
        }
    }
}

// ================= UPDATE =================
void GameManager::actualizar() {
    if (_estado == JUGANDO) {
        _camara.seguir(_personaje.getPosicion());
        _personaje.manejarInput(_mapa);
		_mascota.seguir(_personaje.getPosicion());
		_golem.actualizar(_personaje.getPosicion(), 0.016f); // Asumiendo 60 FPS, cada frame dura ~16ms

		// 🌟 Actualizás la niebla con el tiempo del frame
		_niebla.actualizar(0.016f);
    }
}

// ================= RENDER =================
void GameManager::renderizar() {
    _ventana.clear(sf::Color(30, 30, 30));

    // ===== MENU =====
    if (_estado == MENU) {
        _ventana.setView(_ventana.getDefaultView());
        _menu.draw(_ventana);
    }

    // ===== JUEGO =====
    else if (_estado == JUGANDO) {
        _ventana.setView(_camara.getVista());
        _mapa.dibujarMapa(_ventana);
        _mapa.dibujarDebug(_ventana);

		_personaje.dibujar(_ventana);
		_mascota.dibujar(_ventana);
		_golem.dibujar(_ventana);

		//ULTIMA CAPA DE RENDERIZACION PARA QUE LA NIEBLA ESTE ENCIMA DE TODO
		_niebla.dibujar(_ventana, _camara.getVista());
     
    }

    // ===== CREDITOS =====
    else if (_estado == CREDITOS) {
        _ventana.setView(_ventana.getDefaultView());

        // 🔹 Dibujamos el texto de créditos
        _ventana.draw(_textoCreditos);
    }

    _ventana.display();
}