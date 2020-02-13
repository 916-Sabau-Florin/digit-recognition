#pragma once
#include <iostream>
#include <vector>
#include "Widget.hpp"
#include "Button.hpp"
#include "TextArea.hpp"
#include "PaintArea.hpp"

PaintArea *paintArea;
Button<PaintAreaEvent> *clearButton;


std::vector<Widget*> widgets;

void Init()
{
    paintArea= new PaintArea(sf::IntRect(150,50,500,500));
    clearButton = new Button<PaintAreaEvent>(sf::FloatRect(300.0,600.0,200.0,75.0),"Clear", PaintAreaEvent::Clear ,sf::Color::Red);
    clearButton->addObserver(paintArea);
    widgets.push_back(paintArea);
    widgets.push_back(clearButton);
}

void Update()
{
    for(auto w:widgets)
        w->update();
}

void HandleEvents()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
            return;
        }
        for(auto w:widgets)
            w->handleEvent(event);
    }
}

void Draw()
{
    window.clear(sf::Color::Black);
    for(auto w:widgets)
        window.draw(*w);
    window.display();
}



