#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class MenuButton {
public:
    MenuButton(float x, float y, float w, float h, const std::string& label, sf::Font& font);
    bool isClicked(sf::Vector2i mousePos);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape shape;
    sf::Text text;
};