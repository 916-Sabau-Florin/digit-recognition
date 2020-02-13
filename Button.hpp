#pragma once
#include "Widget.hpp"
#include "Subject.tpp"
#include "TextArea.hpp"

template <class T>
class Button : public Widget, public Subject<T>
{
public:
    Button(const sf::FloatRect &rect, const std::string &text, T message, sf::Color color);

    void handleEvent(sf::Event event);
    void update();
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::RectangleShape _shape;
    TextArea _text;
    T _message;
};

#include "Button.cpp"
