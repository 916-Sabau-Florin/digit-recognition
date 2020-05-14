#pragma once
#include <iostream>
#include <vector>
#include <Widget.hpp>
#include <Button.hpp>
#include <TextArea.hpp>
#include <PaintArea.hpp>
#include <neural_network.hpp>
#include <utils.hpp>

gui::PaintArea *paintArea;
gui::TextArea *digitText;
gui::Button *clearButton;
gui::Button *calculateButton;
gui::Button *small;
gui::Button *medium;
gui::Button *large;


std::vector<gui::Widget*> widgets;




int findDigit(nn::neural_network &NN)
{
    auto inputMatrix = (paintArea->toMatrix(28,28));
    std::vector<double> inputVector = inputMatrix.toVector();

    NN.feedforward(inputVector);
    auto result = NN.getOutput().toVector();
    int digit = 0;
    float mx = 0;
    for(int i=0;i<10;i++)
        if(result[i]>mx)
        {
            //std::cout<<result[i]<<std::endl;
            mx=result[i];
            digit=i;
        }
    return digit;
}

void Init()
{
    nn::neural_network NN({784,64,32,10},
                  {nn::sigmoid,nn::sigmoid,nn::sigmoid,nn::sigmoid},
                   nn::quadratic);
    std::ifstream inBrain("trainedFinal2.txt");
    NN.fromFile(inBrain);

    digitText = new gui::TextArea(sf::FloatRect(600.0,660.0,200.0,75.0),"NaN");

    paintArea= new gui::PaintArea(sf::IntRect(150,50,562,562));
    clearButton = new gui::Button(sf::FloatRect(230.0,660.0,200.0,75.0),"Clear",sf::Color::Red);
    clearButton->setCallback([=]{
        paintArea->clear();
    });
    calculateButton = new gui::Button(sf::FloatRect(450.0,660.0,200.0,75.0),"Calculate", sf::Color::Green);
    calculateButton->setCallback([=]() mutable {
        digitText->setText(std::to_string(findDigit(NN)));
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
    widgets.push_back(digitText);
    widgets.push_back(clearButton);
    widgets.push_back(calculateButton);
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


