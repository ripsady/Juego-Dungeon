#include "GameManager.h"
#include <iostream>
#include "cmath" // Para usar cos() y sin() en spawnearDropSeguro

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

    // ================= ITEMS Y OBJETOS (NUEVO) =================
    // 🧪 Spawneamos ítems de prueba para testear tu nuevo sistema
    Item* pocionDePrueba = _itemManager.crearPocionVida();
	spawnearDropSeguro(pocionDePrueba, _itemManager.getTexturaPocionVida(), 400.f, 300.f); //forzamos a spawnear ahi para verificar que nuestra función de spawn seguro funciona bien (no colisiona con el personaje ni el mapa)

    Item* hornoDePrueba = _itemManager.crearHorno();
    _objectsManager.agregarItemAlMundo(hornoDePrueba, _itemManager.getTexturaHorno(), 550.f, 350.f);

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

                    if (selected == 0) {
                        _estado = JUGANDO;
                        _reloj.restart(); // Reiniciamos el reloj al empezar a jugar para que la niebla funcione bien desde el inicio
                    }
                    else if (selected == 2) { // CREDITOS
                        _estado = CREDITOS;
                    }
                    else if (selected == 3) {
                        _ventana.close();
                    }
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

		// Calculamos el tiempo real del frame para que las actualizaciones sean consistentes sin importar el rendimiento de la máquina
		float dt = _reloj.restart().asSeconds(); // Tiempo del frame en segundos

        _camara.seguir(_personaje.getPosicion());
        _personaje.manejarInput(_mapa);
		_mascota.seguir(_personaje.getPosicion());
        _golem.actualizar(_personaje.getPosicion(), dt);
		_niebla.actualizar(dt);

        // 🌟 CHEQUEO DE ÍTEMS: Nos fijamos si el personaje pisa algo y toca la A
        _objectsManager.chequearInteracciones(_personaje);
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

        // 1. Dibujamos las capas base (Mapa)
        _mapa.dibujarMapa(_ventana);
		_mapa.dibujarDebug(_ventana); // Opcional: dibuja los bloques sólidos en rojo para debuggear las colisiones

        // 🌟 2. Dibujamos los ítems del suelo (arriba del mapa, abajo de las entidades)
        _objectsManager.dibujarItems(_ventana);

        // 3. Dibujamos las entidades
		_personaje.dibujarDebug(_ventana); // Opcional: dibuja la hitbox del personaje en verde para debuggear las colisiones
        _personaje.dibujar(_ventana);
        _mascota.dibujar(_ventana);
        _golem.dibujar(_ventana);

        // 4. Última capa de renderización (Niebla)
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

// ================= FUNCIONES AUXILIARES Y HERRAMIENTAS DEL JUEGO =================
void GameManager::spawnearDropSeguro(Item* item, sf::Texture& textura, float xInicial, float yInicial) {
    float x = xInicial;
    float y = yInicial;
    bool lugarLibre = false;

    // 1. Achicamos la hitbox imaginaria a 16x16 para que la poción sea finita 
    // y pueda entrar en pasillos angostos sin detectar colisión por error.
    sf::FloatRect futuraHitbox(x, y, 16.f, 16.f);

    // 2. Búsqueda en espiral
    float radio = 0.f;
    float angulo = 0.f;
    int intentos = 0;

    // Va a intentar 50 posiciones distintas alrededor del monstruo muerto
    while (intentos < 50) {
        futuraHitbox.left = x;
        futuraHitbox.top = y;

        // 🚨 OJO: Chequeá que tu método se llame "hayColision" o cambialo por el tuyo
        if (!_mapa.hayColision(futuraHitbox)) {
            lugarLibre = true;
            break; // ¡Encontramos un hueco! Rompemos el bucle
        }

        // Si tocó pared, corremos la coordenada un poquito en espiral
        angulo += 0.8f;     // Giramos la dirección
        radio += 2.0f;      // Nos alejamos del centro original

        x = xInicial + std::cos(angulo) * radio;
        y = yInicial + std::sin(angulo) * radio;

        intentos++;
    }

    // 3. Veredicto final
    if (lugarLibre) {
        // La plantamos en la nueva coordenada X e Y corregida
        _objectsManager.agregarItemAlMundo(item, textura, x, y);
    }
    else {
        // Solo la borramos si lo mataste adentro de un pasillo enano 
        // y después de 50 intentos no hubo ni un píxel de lugar
        std::cout << "🧱 Mapa llenísimo. Imposible tirar el drop." << std::endl;
        delete item;
    }
}