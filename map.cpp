#include "map.h"
#include <iostream>
#include <fstream> // para poder abrir y leer archivos CSV
#include <sstream> // para separar los numeros del CSV usando las comas

using namespace std;

Map::Map(int tamTile, float escala) {
	_tamTile = tamTile; // Guardamos el valor de tamaño del tile para usarlo al dibujar el mapa
	_escala = escala; // Guardamos el valor de escala para usarlo al dibujar el mapa
	_filas = 0; // arranca en 0 para luego asignar el valor correcto al cargar el mapa
	_columnas = 0; // arranca en 0 para luego asignar el valor correcto al cargar el mapa

	// Le aplicamos la escala al sprite auxiliar para que se dibuje con el tamaño correcto (2.0f)
	_spriteTile.setScale(_escala, _escala);
}

bool Map::cargarMapa(const string& csvPath, const string& texturaPath) {

	// === EL "CLEAN" DE SEGURIDAD ===
	_filas = 0;
	_columnas = 0;
	mapa.clear(); // Vacía por completo el vector de vectores, liberando la memoria anterior

	// Cargar la imagen de SFML
	if (!_texture.loadFromFile(texturaPath)) {
		cout << "❌ ERROR: No se pudo cargar la imagen del tileset en: " << texturaPath << endl;
		return false; // corta la funcion si no la encuentra
	}

	// Configuramos la textura nitida y se la pasamos al sprite
	_texture.setSmooth(false); // Pixel art nítido
	_spriteTile.setTexture(_texture);

	// Abrir el archivo CSV con fstream
	ifstream archivo(csvPath);
	if (!archivo.is_open()) {
		cout << "❌ ERROR: No se pudo abrir el archivo del mapa en: " << csvPath << endl;
		return false; // corta la funcion si no lo encuentra
	}

	// Limpiamos la matriz por seguridad antes de meterle datos
	mapa.clear();

	// =================================================================================================================================
	// LA HISTORIA DE LA FÁBRICA DE ALFAJORES: De texto chato CSV a matriz en memoria
	// =================================================================================================================================
	string linea; // Nuestra mesa de trabajo donde bajamos un renglón entero del archivo (ej: "10,10,10")

	// CAMIÓN REPARTIDOR: Mientras queden palets (renglones) en el camión (archivo), bajamos uno a la mesa de trabajo
	while (getline(archivo, linea)) {

		// Control de calidad: Limpiamos los saltos de línea invisibles de Windows (\r) para que no ensucien los datos
		if (!linea.empty() && linea.back() == '\r') {
			linea.pop_back();
		}

		stringstream ss(linea); // LA CORTADORA: Metemos la tira de texto en la máquina para procesarla por partes
		string valor;           // ALFAJOR SUELTO: Acá guardamos el pedacito de texto recortado entre comas (ej: "10")
		vector<int> filaActual; // LA CAJA LARGA: El tubo temporal donde el operario va a ir acomodando los alfajores de esa fila

		// EL OPERARIO CON LA TIJERA: Mientras la cortadora encuentre comas (','), corta y nos da un alfajor suelto en texto
		while (getline(ss, valor, ',')) {
			if (!valor.empty()) {
				// EL ENVOLTORIO: "stoi" le saca el plástico al texto "10" y lo transforma en el número matemático 10.
				// Luego, ".push_back" mete ese alfajor en la caja larga (filaActual), acomodándolo al final de la fila.
				filaActual.push_back(stoi(valor));
			}
		}

		// EL ESTANTE DEL DEPÓSITO: Cuando el operario terminó de llenar la caja larga con toda la fila horizontal...
		if (!filaActual.empty()) {
			// ... agarramos la caja completa y la acomodamos en el estante de nuestra gran matriz (mapa), de arriba hacia abajo.
			mapa.push_back(filaActual);
		}
		// El camión avanza al siguiente palet (renglón) y se repite la historia...
	}

	// === AQUÍ SE CORRIGIÓ EL CIERRE DE CARGAR MAPA ===
	// Registramos las dimensiones reales que se auto-detectaron en los vectores
	_filas = mapa.size();
	if (_filas > 0) {
		_columnas = mapa[0].size();
	}
	else {
		_columnas = 0;
	}



	return true;
} // <- Llave de cierre obligatoria de cargarMapa

// =================================================================================================================================
// FUNCIÓN PARA DIBUJAR EL MAPA COMPLETO EN LA PANTALLA
// =================================================================================================================================
void Map::dibujarMapa(sf::RenderWindow& ventana) {
	// 1. calculamos cuantas columnas de tiles tiene el tileset dividiendo el ancho total de la imagen por el tamaño de cada tile
	int columnasEnTileset = _texture.getSize().x / _tamTile;





	// 2. Recorremos la matriz del mapa con dos for anidados para dibujar cada tile en su posición correspondiente
	for (int f = 0; f < _filas; f++) {
		for (int c = 0; c < _columnas; c++) {

			int tileID = mapa[f][c]; // Sacamos el numero del alfajor que corresponde a esa posición

			

			// En Tiled, el número 0 significa "vacío" (no hay nada dibujado).
			if (tileID > 0) {

			
				int actualTileID = tileID;

				// 3. EL ALGORITMO DE RECORTE: Calculamos la posición exacta en píxeles dentro del Tileset (PNG)
				int pixelX_enTileset = (actualTileID % columnasEnTileset) * _tamTile;
				int pixelY_enTileset = (actualTileID / columnasEnTileset) * _tamTile;

				// Le decimos al sprite qué cuadradito recortar de la textura gigante
				_spriteTile.setTextureRect(sf::IntRect(pixelX_enTileset, pixelY_enTileset, _tamTile, _tamTile));

				// Calculamos la posición en píxeles reales DENTRO DE LA VENTANA del juego (escalado x2)
				float pantallaX = c * _tamTile * _escala;
				float pantallaY = f * _tamTile * _escala;

				// Ubicamos el sprite en sus coordenadas de pantalla y lo dibujamos
				_spriteTile.setPosition(pantallaX, pantallaY);
				ventana.draw(_spriteTile);
			}
		}
	}
}