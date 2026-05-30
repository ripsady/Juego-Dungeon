#pragma once
#include <SFML/Graphics.hpp>
#include "Inventario.h"
#include <iostream>
#include <string>

class UI_Inventario {
private:
    sf::RectangleShape _slotFondo;
    float _tamanioSlot;
    float _margen;
    sf::Font _fuente;
    sf::Text _textoCantidad;


    // 🌟 VARIABLES DE DEBUG: Para mover en caliente
    float _desfaseX;
    float _desfaseY;
    float _origenX;
    float _origenY;

public:
    UI_Inventario();
    void dibujar(sf::RenderWindow& ventana, const Inventario& mochila);

    // 🌟 MÉTODOS DE CONTROL: Para que el GameManager le avise qué cambiar
    void ajustarPosicion(float x, float y);
    void ajustarOrigen(float x, float y);
};

// Implementaciones inline para evitar símbolos sin resolver si el .cpp no está añadido al proyecto
inline UI_Inventario::UI_Inventario() {
    _tamanioSlot = 50.f;
    _margen = 10.f;

    _desfaseX = 0.f;
    _desfaseY = 0.f;
    _origenX = 0.f;
    _origenY = 0.f;

    _slotFondo.setSize(sf::Vector2f(_tamanioSlot, _tamanioSlot));
    _slotFondo.setFillColor(sf::Color(40, 40, 40, 200));
    _slotFondo.setOutlineColor(sf::Color::White);
    _slotFondo.setOutlineThickness(2.f);

    if (!_fuente.loadFromFile("assets/NorthEternal-yYl4V.otf")) {
        std::cout << "❌ Error: No se encontró la fuente para el inventario." << std::endl;
    }

    _textoCantidad.setFont(_fuente);
    _textoCantidad.setCharacterSize(14);
    _textoCantidad.setFillColor(sf::Color::White);
    _textoCantidad.setOutlineColor(sf::Color::Black);
    _textoCantidad.setOutlineThickness(1.f);
}

inline void UI_Inventario::ajustarPosicion(float x, float y) {
    _desfaseX += x;
    _desfaseY += y;
    std::cout << "📍 HUD Pos -> DesfaseX: " << _desfaseX << " | DesfaseY: " << _desfaseY << std::endl;
}

inline void UI_Inventario::ajustarOrigen(float x, float y) {
    _origenX += x;
    _origenY += y;
    std::cout << "🎯 HUD Origen -> X: " << _origenX << " | Y: " << _origenY << std::endl;
}

inline void UI_Inventario::dibujar(sf::RenderWindow& ventana, const Inventario& mochila) {
    sf::View vistaOriginal = ventana.getView();
    ventana.setView(ventana.getDefaultView());

    _slotFondo.setOrigin(_origenX, _origenY);

    const std::vector<Item*>& items = mochila.getSlots();
    int cantidadSlotsVisibles = 5;

    float anchoTotal = (cantidadSlotsVisibles * _tamanioSlot) + ((cantidadSlotsVisibles - 1) * _margen);

    float startX = ((ventana.getSize().x - anchoTotal) / 2.f) + _desfaseX;
    float startY = (ventana.getSize().y - _tamanioSlot - 20.f) + _desfaseY;

    for (int i = 0; i < cantidadSlotsVisibles; i++) {
        float posX = startX + i * (_tamanioSlot + _margen);

        _slotFondo.setPosition(posX, startY);
        ventana.draw(_slotFondo);

        if (i < items.size() && items[i] != nullptr) {
            sf::Sprite spriteItem = items[i]->getSprite();
            spriteItem.setPosition(posX + 9.f, startY + 9.f);
            ventana.draw(spriteItem);

            int cantidad = items[i]->getCantidad();
            if (cantidad > 1) {
                _textoCantidad.setString(std::to_string(cantidad));
                _textoCantidad.setPosition(posX + _tamanioSlot - 20.f, startY + _tamanioSlot - 20.f);
                ventana.draw(_textoCantidad);
            }
        }
    }

    ventana.setView(vistaOriginal);
}
