#pragma once
#include <SFML/Graphics.hpp>

namespace gui {

class Widget : public sf::Drawable
{
public:
    ~Widget() override = 0;
    virtual void update() = 0;
    virtual void handleEvent(sf::Event event) = 0;
protected:
//    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

}
