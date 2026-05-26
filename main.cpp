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
    JUGANDO,
    CREDITOS,
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

    // Crea el mapa con tamaño de tile 16 píxeles y escala 2 (se verá el doble de grande)
    Map mapa(16, 2.0f);

    // Carga el mapa y verifica si cargó correctamente
    if (!mapa.cargarMapa("assets/mapa_v1.csv", "assets/Dungeon_Tileset.png")) {
        cout << "No se pudo cargar el mapa. Cerrando el juego." << endl;
        return -1;
    }

    // Crea el objeto personaje (llama automáticamente al constructor de Personaje)
    Personaje personaje;

    // Crea el objeto mascota (llama automáticamente al constructor de Mascota)
    Mascota mascota;

    // CREACIÓN Y CONFIGURACIÓN DEL TEXTO DE CRÉDITOS
    sf::Font font;
    // Declara un objeto de tipo sf::Font
    // Este objeto representa una fuente tipográfica que se utilizará para renderizar texto en pantalla

    font.loadFromFile("assets/ariali.ttf");
    // Carga la fuente desde un archivo externo (.ttf)
    // Es obligatorio cargar una fuente antes de usarla en un sf::Text
    // Si este archivo no existe o la ruta es incorrecta, el texto NO se mostrará

    sf::Text creditosText;
    // Declara un objeto de tipo sf::Text
    // Este objeto representa un texto que puede ser dibujado en la ventana

    creditosText.setFont(font);
    // Asocia la fuente previamente cargada al objeto de texto
    // Sin esta línea, SFML no sabría con qué tipografía renderizar el texto

    creditosText.setString(
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
    );
    // Define el contenido textual que se mostrará en pantalla
    // Puede incluir saltos de línea usando "\n" si querés múltiples líneas

    creditosText.setCharacterSize(30);
    // Define el tamaño de los caracteres en píxeles
    // A mayor valor, más grande se verá el texto en pantalla

    creditosText.setFillColor(sf::Color::White);
    // Establece el color del texto
    // En este caso, blanco (RGB: 255,255,255)
    // También podrías usar colores personalizados

    creditosText.setPosition(150, 150);
    // Define la posición del texto dentro de la ventana
    // (150,150) significa:
    // - 150 píxeles desde el borde izquierdo (eje X)
    // - 150 píxeles desde el borde superior (eje Y)

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

                        // Si seleccionamos "Creditos" Muestra la pantalla de los creditos
                        if ( selected == 2 ) {
							estado = CREDITOS;
                        }

                        // Si seleccionó "Salir", cierra el juego
                        if (selected == 3) {
                            ventana.close();
                        }
                    }
                }
            }

            // CONTROL DE INPUT EN EL ESTADO "CREDITOS"
            if (estado == CREDITOS) {
                // Verifica si el juego se encuentra actualmente en el estado "CREDITOS"
                // Es decir, si el usuario está visualizando la pantalla de créditos

                if (evento.type == sf::Event::KeyPressed) {
                    // Comprueba si el evento capturado corresponde a una tecla presionada
                    // (KeyPressed se dispara UNA sola vez cuando se presiona la tecla)

                    if (evento.key.code == sf::Keyboard::Escape) {
                        // Verifica específicamente si la tecla presionada fue "ESCAPE"
                        // Esta tecla se usa comúnmente como acción de "volver atrás" o "salir"

                        estado = MENU;
                        // Cambia el estado actual del juego a "MENU"
                        // Esto provoca que:
                        // - Se deje de mostrar la pantalla de créditos
                        // - Se vuelva a renderizar el menú principal
                        // - Se reactive la lógica de input del menú
                    }
                }
            }
        }

        // =========================
        // LÓGICA SEGÚN ESTADO
        // =========================
        if (estado == JUGANDO) {
            // Lee el teclado y mueve el personaje según la tecla presionada
            personaje.manejarInput();

            // La mascota sigue automáticamente al personaje
            mascota.seguir(personaje.getPosicion());
        }

        // =========================
        // RENDER SEGÚN ESTADO
        // =========================

        // Borra lo dibujado en el frame anterior para empezar limpio
        ventana.clear(sf::Color(30, 30, 30));

        if (estado == MENU) {
            // Dibuja la interfaz del menú principal
            menu.draw(ventana);
        }
        else if (estado == JUGANDO) {
            // Dibuja el mapa primero para que quede detrás del personaje
            mapa.dibujarMapa(ventana);

            // Dibuja el personaje encima del mapa
            personaje.dibujar(ventana);

            // Dibuja la mascota encima del mapa
            mascota.dibujar(ventana);
        } else if ( estado == CREDITOS ) {
            // Evalúa si el estado actual del juego es "CREDITOS"
            // Este bloque se ejecuta únicamente cuando el usuario está en la pantalla de créditos

            // Dibuja el objeto de texto que contiene la información de los créditos
            // (nombre del juego, autores, etc.)
            ventana.draw(creditosText);

            // "creditosText" es un sf::Text previamente configurado (fuente, tamaño, posición, contenido)
            // Este draw lo envía al buffer de render de la ventana, pero NO se muestra aún

            // La visualización final ocurre cuando se llama a:
            // ventana.display();
            // al final del frame (doble buffering de SFML)
        }

        // Muestra en pantalla todo lo que se dibujó en este frame
        ventana.display();
    }

    return 0;
}