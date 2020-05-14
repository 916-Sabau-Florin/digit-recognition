#include <SFML/Graphics.hpp>
#include <Resources.hpp>
#include <App.hpp>
#include <iostream>



int main()
{
    LoadResources();
    Init();

    while(window.isOpen())
    {
        Update();
        HandleEvents();
        Draw();
    }

    return 0;
}
