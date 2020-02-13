#include "PaintArea.hpp"

PaintArea::PaintArea(const sf::IntRect &rect) : _width(rect.width), _height(rect.height)
{
    _texture.create(rect.width,rect.height);

    _pixels = new sf::Uint8[4*(rect.width*rect.height)];

    std::memset(_pixels,0xff,4*(rect.width*rect.height));
    _texture.update(_pixels);
    _sprite.setTexture(_texture);
    _sprite.setPosition(rect.left,rect.top);

}


PaintArea::~PaintArea()
{
    delete[] _pixels;
}

void PaintArea::onNotify(PaintAreaEvent message)
{
    std::cout<<2;
    if(message==PaintAreaEvent::Clear)
    {
        this->clear();
    }
}

void PaintArea::handleEvent(sf::Event event) {}

void PaintArea::clear()
{
    for(int i=1;i<_height;i++)
        for(int j=1;j<_width;j++)
            setColor(j,i,sf::Color::White);
}

void PaintArea::update()
{
    std::cout<<sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)<<' '<<sf::Mouse::getPosition(window).x<<' '<<sf::Mouse::getPosition(window).y<<'\n';
    _texture.update(_pixels);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        auto pos=sf::Mouse::getPosition(window)-sf::Vector2i(_sprite.getPosition());
        bool vis[_width*_height] = {};
        paint(vis,pos.x-1,pos.y-1,pos.x-1,pos.y-1,20,sf::Color::Black);
        delete[] vis;
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
        auto pos=sf::Mouse::getPosition(window)-sf::Vector2i(_sprite.getPosition());
        bool vis[_width*_height] = {};
        paint(vis,pos.x-1,pos.y-1,pos.x-1,pos.y-1,20,sf::Color::White);
        delete[] vis;
    }
}

void PaintArea::paint(bool vis[],int x, int y,int x0,int y0, int radius,sf::Color color)
{

    if((x-x0)*(x-x0)+(y-y0)*(y-y0) > radius*radius)
        return;
    if(x<1 || x>=_width-1 || y<1 || y>=_height-1)
        return;
    if(vis[x+y*_width])
        return;
    vis[x+y*_width]=1;

    setColor(x,y,color);
    paint(vis,x+1,y,x0,y0,radius,color);
    paint(vis,x,y+1,x0,y0,radius,color);
    paint(vis,x-1,y,x0,y0,radius,color);
    paint(vis,x,y-1,x0,y0,radius,color);
}

sf::Color PaintArea::getColor(int x, int y)
{
    int r=_pixels[(y*_width+x)*4];
    int g=_pixels[(y*_width+x)*4+1];
    int b=_pixels[(y*_width+x)*4+2];
    int a=_pixels[(y*_width+x)*4+3];
    return sf::Color(r,g,b,a);
}

void PaintArea::setColor(int x,int y, sf::Color color)
{
    _pixels[(y*_width+x)*4]  =color.r;
    _pixels[(y*_width+x)*4+1]=color.g;
    _pixels[(y*_width+x)*4+2]=color.b;
    //_pixels[(y*_width+x)*4+3]=color.a;
}

void PaintArea::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite);
}
