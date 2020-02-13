#pragma once
#include <iostream>
#include <cstring>
#include "Resources.hpp"
#include "Widget.hpp"
#include "Observer.tpp"
#include "Subject.tpp"

enum PaintAreaEvent {
    Clear
};

class PaintArea : public Widget, public Observer<PaintAreaEvent>, public Subject<int>
{
public:
    PaintArea(const sf::IntRect &rect);
    ~PaintArea();

    void update();
    void handleEvent(sf::Event event);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void onNotify(PaintAreaEvent message);

private:
    void paint(bool vis[],int x,int y,int x0,int y0,int radius,sf::Color color);
    void clear();
    void setColor(int x,int y,sf::Color color);
    sf::Color getColor(int x,int y);


    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Uint8 *_pixels;
    int _width,_height;
};
