#pragma once
#include <iostream>
#include <cstring>
#include <Resources.hpp>
#include <Widget.hpp>


namespace gui {

class PaintArea : public Widget
{
public:
    PaintArea(const sf::IntRect &rect);
    ~PaintArea();

    void update();
    void setRadius(float radius);
    void handleEvent(sf::Event event);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void clear();

private:
    void paint(int x0,int y0,int x1,int y1,sf::Color color);
    void setColor(int x,int y,sf::Color color);
    sf::Color getColor(int x,int y);


    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Uint8 *_pixels;
    sf::Vector2i _point;
    float _radius;
    int _width,_height;
};

}
