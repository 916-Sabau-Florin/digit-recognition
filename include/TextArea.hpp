#pragma once
#include <Widget.hpp>

namespace gui {

class TextArea : public Widget
{
public:
    TextArea(const sf::FloatRect &rect, const std::string &str);
    ~TextArea();
    void handleEvent(sf::Event event);
    void center();
    void update();

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:

    sf::Text _text;
    sf::FloatRect _rect;
};

}
