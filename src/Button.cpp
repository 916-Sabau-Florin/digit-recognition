#pragma once
#include <iostream>
#include <Button.hpp>
#include <Resources.hpp>
#include <functional>

namespace gui {

Button::Button(const sf::FloatRect &rect, const std::string &text, sf::Color color) : _text(rect,text)
{
    _shape.setPosition(rect.left,rect.top);
    _shape.setSize(sf::Vector2f(rect.width,rect.height));
    _shape.setFillColor(color);
    //_callback=[]{};
}


void Button::handleEvent(sf::Event event)
{
    sf::FloatRect rect=_shape.getGlobalBounds();
    switch(event.type)
    {
        case sf::Event::MouseButtonPressed:
            if(rect.contains(event.mouseButton.x,event.mouseButton.y))
               this->_callback();
            break;
    }
}

void Button::setCallback(std::function<void()> callback)
{
    _callback = callback;
}

void Button::update() {
    _text.update();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_shape);
    target.draw(_text);
}

}
