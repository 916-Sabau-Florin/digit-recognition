#pragma once
#include <Widget.hpp>

namespace gui {

class TextArea : public Widget
{
public:
    TextArea(const sf::FloatRect &rect, const std::string &str);
    ~TextArea() override;
    void handleEvent(sf::Event event) override;
    void center();
    void update() override;
    void setText(const std::string &str);

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


private:

    sf::Text _text;
    sf::FloatRect _rect;
};

}
