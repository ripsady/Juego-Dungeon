#include "menu.h"

Menu::Menu(float width, float height) {
    font.loadFromFile("assets/ariali.ttf");

    std::string items[] = {
        "Inicio",
        "Logros",
        "Creditos",
        "Salir"
    };

    for (int i = 0; i < 4; i++)
    {
        sf::Text text;
        text.setFont(font);
        text.setString(items[i]);
        text.setCharacterSize(40);
        text.setPosition(width / 2 - 100, height / (5 + 1) * (i + 1));

        if (i == 0)
            text.setFillColor(sf::Color::Red);
        else
            text.setFillColor(sf::Color::White);

        opciones.push_back(text);
    }

    selectedIndex = 0;
}

void Menu::draw(sf::RenderWindow& window) {
    for (auto& opcion : opciones)
        window.draw(opcion);
}

void Menu::moveUp() {
    if (selectedIndex > 0) {
        opciones[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex--;
        opciones[selectedIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedIndex < opciones.size() - 1) {
        opciones[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex++;
        opciones[selectedIndex].setFillColor(sf::Color::Red);
    }
}

int Menu::getSelectedIndex() { // 👈 FIX
    return selectedIndex;
}