#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;


int main()
{
    sf::RenderWindow window(sf::VideoMode(1540, 700), "Covid-19 Map");
    #include "countries.h"


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        #include "draw.h"
        window.display();

    }

    return 0;
}
