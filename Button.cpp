#pragma once
#include <iostream>
#include "Button.hpp"
#include "Resources.hpp"

template <class T>
Button<T>::Button(const sf::FloatRect &rect, const std::string &text, T message, sf::Color color) : _text(rect,text), _message(message)
{
    _shape.setPosition(rect.left,rect.top);
    _shape.setSize(sf::Vector2f(rect.width,rect.height));
    _shape.setFillColor(color);
}

template <class T>
void Button<T>::handleEvent(sf::Event event)
{
    sf::FloatRect rect=_shape.getGlobalBounds();
    switch(event.type)
    {
        case sf::Event::MouseButtonPressed:
            if(rect.contains(event.mouseButton.x,event.mouseButton.y))
               this->notify(_message);
            break;
    }
}

template <class T>
void Button<T>::update() {
    _text.update();
}

template <class T>
void Button<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_shape);
    target.draw(_text);
}
