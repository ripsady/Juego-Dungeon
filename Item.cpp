#include "Item.h"
#include <iostream>

// ========================================================
// 1. IMPLEMENTACIÓN DE LA CLASE BASE (Item)
// ========================================================

Item::Item(int id, std::string nombre, TipoItem tipo, int cantidad, int maxStack, bool esAgarrable)
    : _id(id), _nombre(nombre), _tipo(tipo), _cantidad(cantidad), _maxStack(maxStack), _esAgarrable(esAgarrable), _estaEnElMundo(false) {
}

void Item::colocarEnMundo(sf::Texture& textura, float x, float y, sf::FloatRect hitboxCustom) {
    _sprite.setTexture(textura);
    _sprite.setPosition(x, y);
    _estaEnElMundo = true;

    if (hitboxCustom.width > 0 && hitboxCustom.height > 0) {
        _hitbox = hitboxCustom;
    }
    else {
        _hitbox = _sprite.getGlobalBounds();
    }
}

void Item::dibujar(sf::RenderWindow& ventana) {
    if (_estaEnElMundo) {
        ventana.draw(_sprite);
    }
}

// ========================================================
// 2. IMPLEMENTACIÓN DE LAS CLASES HIJAS
// ========================================================

// --- CONSUMIBLE ---
// Pasamos: TipoItem::Consumible, stack de 64, y esAgarrable = true
Consumible::Consumible(int id, std::string nombre, float cura, int cantidad)
    : Item(id, nombre, TipoItem::Consumible, cantidad, 64, true), _curacion(cura) {
}

void Consumible::usar(Personaje& jugador) {
    std::cout << "🍎 Consumiste " << _nombre << ". Te curaste " << _curacion << " de vida." << std::endl;
}


// --- MUEBLE ---
// Pasamos: TipoItem::Mueble, stack de 1, y esAgarrable = false (fijo en el piso)
Mueble::Mueble(int id, std::string nombre, int tipoMueble)
    : Item(id, nombre, TipoItem::Mueble, 1, 1, false), _tipoMueble(tipoMueble) {
}

void Mueble::usar(Personaje& jugador) {
    if (_tipoMueble == 1) std::cout << "🏺 Abriendo Caldero..." << std::endl;
    else if (_tipoMueble == 2) std::cout << "🔥 Abriendo Horno..." << std::endl;
}


// --- RECURSO ---
// Pasamos: TipoItem::Recurso, stack de 999, y esAgarrable = true
Recurso::Recurso(int id, std::string nombre, int tipoRecurso, int cantidad)
    : Item(id, nombre, TipoItem::Recurso, cantidad, 999, true), _tipoRecurso(tipoRecurso) {
}

void Recurso::usar(Personaje& jugador) {
    std::cout << "🪵 Es un recurso material, no se puede 'usar' directo. Sirve para craftear." << std::endl;
}


// --- EQUIPAMIENTO ---
// Pasamos: TipoItem::Equipamiento, stack de 1, y esAgarrable = true
Equipamiento::Equipamiento(int id, std::string nombre, int tipoEquipamiento, int bonusAtaque, int bonusDefensa)
    : Item(id, nombre, TipoItem::Equipamiento, 1, 1, true), _tipoEquipamiento(tipoEquipamiento), _bonusAtaque(bonusAtaque), _bonusDefensa(bonusDefensa) {
}

void Equipamiento::usar(Personaje& jugador) {
    std::cout << "⚔️ Equipaste " << _nombre << ". (+Ataque: " << _bonusAtaque << " | +Defensa: " << _bonusDefensa << ")" << std::endl;
}