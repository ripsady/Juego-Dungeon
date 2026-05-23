#pragma once
#include <SFML/Graphics.hpp> //Para usar sf::Sprite, sf::Texture, etc.
#include <vector>	// Para crear la matriz del mapa
#include <string> // Para manejar rutas de archivos

using namespace std;

class Map {
private:
	//atributos privados del mapa
	
	vector<vector<int>> mapa; // Matriz del mapa
	int _filas; //Filas del mapa
	int _columnas; //Columnas del mapa
	int _tamTile; //Tamaño del tile en píxeles
	float _escala; //Escala para agrandar el tile

	sf::Texture _texture; //La imagen del tileset	
	sf::Sprite _spriteTile; //Sprite auxiliar para dibujar cada tile

public:
//Metodos públicos del mapa
Map(int tamTile = 16, float escala = 2.0f); //constructor del mapa con sus valores iniciales

// Cargar el mapa desde un archivo CSV devuelve true si se cargo correctamente, false si hubo un error
bool cargarMapa(const string& csvPath, const string& texturaPath);

//Funcion para dibujar el mapa en la ventana

void dibujarMapa(sf::RenderWindow& ventana);

};
