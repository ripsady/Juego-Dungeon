#pragma once
#include <SFML/Graphics.hpp>
#include "Item.h" // Porque necesitamos conocer a Consumible, Mueble, etc.

class ItemManager {
private:
    // Guardamos las texturas acá para no saturar la memoria RAM
    sf::Texture _texturaPocionVida;
    sf::Texture _texturaHorno;

public:
    ItemManager(); // El constructor va a cargar las imágenes al arrancar el juego

    // 🏭 Métodos de fabricación (Devuelven el objeto ya configurado)
    Item* crearPocionVida();
    Item* crearHorno();

    // 🖼️ Getters para que el ObjectsManager pueda usar las texturas
    sf::Texture& getTexturaPocionVida() { return _texturaPocionVida; }
    sf::Texture& getTexturaHorno() { return _texturaHorno; }
};