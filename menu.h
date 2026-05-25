#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Menu
{
private:
    int selectedIndex;
    std::vector<sf::Text> opciones;
    sf::Font font;

public: // 👈 TODO lo que usás desde main VA ACÁ
    Menu(float width, float height);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedIndex();
};