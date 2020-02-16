#pragma once
#include <Widget.hpp>
#include <TextArea.hpp>
#include <functional>

namespace gui {

class Button : public Widget
{
public:
    Button(const sf::FloatRect &rect, const std::string &text, sf::Color color);

    void handleEvent(sf::Event event);
    void update();
    void setCallback(std::function<void()> callback);

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::RectangleShape _shape;
    TextArea _text;
    std::function<void()> _callback;
};

}
