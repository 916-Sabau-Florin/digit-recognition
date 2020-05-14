#include <PaintArea.hpp>

namespace gui {


PaintArea::PaintArea(const sf::IntRect &rect) : _width(rect.width), _height(rect.height), _radius(20.0)
{
    _texture.create(rect.width,rect.height);

    _pixels = new sf::Uint8[4*(rect.width*rect.height)];

    std::memset(_pixels,0xff,4*(rect.width*rect.height));
    clear();
    _texture.update(_pixels);
    _sprite.setTexture(_texture);
    _sprite.setPosition(rect.left,rect.top);

}


PaintArea::~PaintArea()
{
    delete[] _pixels;
}


void PaintArea::handleEvent(sf::Event event) {}

void PaintArea::clear()
{
    for(int i=1;i<_height-1;i++)
        for(int j=1;j<_width-1;j++)
            setColor(j,i,sf::Color::Black);
    _texture.update(_pixels);
}

void PaintArea::setRadius(float radius)
{
    _radius=radius;
}

void PaintArea::update()
{

    auto pos=sf::Mouse::getPosition(window)-sf::Vector2i(_sprite.getPosition());


    if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        _point=pos;

    if(pos.x<1||pos.x>_width||pos.y<1||pos.y>_height)
    {
        _point=pos;
        return;
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        paint(_point.x-1,_point.y-1,pos.x-1,pos.y-1,sf::Color::White);
        _point=pos;
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
        paint(_point.x-1,_point.y-1,pos.x-1,pos.y-1,sf::Color::Black);
        _point=pos;
    }

    _texture.update(_pixels);
}

float dist_sq(float x0,float y0,float x1,float y1)
{
    return (x0-x1)*(x0-x1)+(y0-y1)*(y0-y1);
}

float distance_sq(float x,float y,float x0,float y0,float x1,float y1)
{
    const float l2 = dist_sq(x0,y0,x1,y1);  // i.e. |w-v|^2 -  avoid a sqrt
    if (l2 == 0) return dist_sq(x,y,x0,y0);   // v == w case
            // Consider the line extending the segment, parameterized as v + t (w - v).
            // We find projection of point p onto the line.
            // It falls where t = [(p-v) . (w-v)] / |w-v|^2
            // We clamp t from [0,1] to handle points outside the segment vw.
    float t = ((x-x0)*(x1-x0)+ (y-y0)*(y1-y0)) / l2;
    t=std::min(1.0f,t);
    t=std::max(0.0f,t);
    const float projectionX = x0 + t * (x1 - x0);
    const float projectionY = y0 + t * (y1 - y0);
    return dist_sq(x,y,projectionX,projectionY);
}

void PaintArea::paint(int x0,int y0,int x1,int y1, sf::Color color)
{
    for(int y=1;y<_height-1;y++)
    {
        for(int x=1;x<_width-1;x++)
        {
            if(distance_sq(x,y,x0,y0,x1,y1)<_radius*_radius)
                setColor(x,y,color);
        }
    }
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

nn::matrix<double> PaintArea::toMatrix(int r,int c)
{
    nn::matrix<double> result(r,c);
    for(int y=0;y<r;y++)
    {
        for(int x=0;x<c;x++)
        {
            double op=0;
            for(int j=0;j<_height/r;j++)
                for(int i=0;i<_width/c;i++)
                    op+=getColor(x*(_width/c)+i+1,y*(_height/r)+j+1)==sf::Color::White?1:0;
            result[{x,y}]=op/((_height/r)*(_width/c));
        }
    }
    return result;
}

}
