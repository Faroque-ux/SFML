#include "MenuButton.h"

MenuButton::MenuButton(float x, float y, float w, float h, const std::string& label, sf::Font& font) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(w, h));
    shape.setFillColor(sf::Color(70, 70, 70));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(28);
    text.setFillColor(sf::Color::White);
    sf::FloatRect tb = text.getLocalBounds();
    text.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
    text.setPosition(x + w / 2.f, y + h / 2.f);
}

bool MenuButton::isClicked(sf::Vector2i mousePos) {
    return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void MenuButton::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}