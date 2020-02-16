#include <Resources.hpp>

namespace gui {

sf::Font font;

}

sf::RenderWindow window;

void LoadResources()
{
    window.create(sf::VideoMode(1366,768),"SFML doesn't work");
    gui::font.loadFromFile("Roboto-Regular.ttf");
}
