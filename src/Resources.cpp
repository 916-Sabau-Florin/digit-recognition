#include <Resources.hpp>

namespace gui {

sf::Font font;

}

sf::RenderWindow window;

void LoadResources()
{
    window.create(sf::VideoMode(920,768),"Digit Recognition");
    gui::font.loadFromFile("Roboto-Regular.ttf");
}
