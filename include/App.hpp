#pragma once
#include <iostream>
#include <vector>
#include <Widget.hpp>
#include <Button.hpp>
#include <TextArea.hpp>
#include <PaintArea.hpp>



gui::PaintArea *paintArea;
gui::Button *clearButton;
gui::Button *small;
gui::Button *medium;
gui::Button *large;

std::vector<gui::Widget*> widgets;

void Init()
{
    paintArea= new gui::PaintArea(sf::IntRect(150,50,560,560));
    clearButton = new gui::Button(sf::FloatRect(330.0,660.0,200.0,75.0),"Clear",sf::Color::Red);
    clearButton->setCallback([=]{
        paintArea->clear();
    });

    small = new gui::Button(sf::FloatRect(710.0,100.0,120.0,60.0),"small",sf::Color::Blue);
    medium = new gui::Button(sf::FloatRect(710.0,170.0,120.0,60.0),"medium",sf::Color::Blue);
    large = new gui::Button(sf::FloatRect(710.0,240.0,120.0,60.0),"large",sf::Color::Blue);

    small->setCallback([=] {
        paintArea->setRadius(10);
    });

    medium->setCallback([=] {
        paintArea->setRadius(20);
    });

    large->setCallback([=] {
        paintArea->setRadius(30);
    });

    widgets.push_back(paintArea);
    widgets.push_back(clearButton);
    widgets.push_back(small);
    widgets.push_back(medium);
    widgets.push_back(large);
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


