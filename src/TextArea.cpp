#include <TextArea.hpp>
#include <Resources.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

namespace gui {

TextArea::TextArea(const sf::FloatRect &rect, const std::string &str) : _rect(rect)
{
    _text.setString(str);
    _text.setFont(font);
    _text.setCharacterSize(30);
}

TextArea::~TextArea() {}

void TextArea::handleEvent(sf::Event event) { }
void TextArea::update() {
    center();
}

void TextArea::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_text);
}

void TextArea::setText(const std::string &str)
{
    _text.setString(str);
}

void TextArea::center()
{
    sf::FloatRect textRect = this->_text.getLocalBounds();
    float diffX=_rect.width - textRect.width;
    float diffY=_rect.height - textRect.height;

    this->_text.setPosition(_rect.left + diffX /2.0f - textRect.left,
                      _rect.top  + diffY/2.0f - textRect.top);
}

}
