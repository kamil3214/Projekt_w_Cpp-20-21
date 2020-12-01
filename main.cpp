#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>

using namespace std;

vector <int> cumulative(vector <string> countries, vector <string> countriesAndTerritories, vector <int> cases )
{
    vector <int> cumulative_cases(194, 0);
    int countries_size = static_cast<int>(countries.size());
    int countriesAndTerritories_size = static_cast<int>(countriesAndTerritories.size());
    for(int i=0; i<countries_size; i++)
    {
        for(int z = 0; z<countriesAndTerritories_size; z++)
        {
            if (countries[i] == countriesAndTerritories[z])
            {
                cumulative_cases[i] = cumulative_cases[i] + cases[z];

            }

        }
        cout<<countries[i]<<": "<< cumulative_cases[i]<<endl;
    }
    return cumulative_cases;

}

vector <sf::Sprite > cumulative_draw(vector <sf::Sprite > sprites, vector <int> cumulative_cases)
{
    int maximum = *max_element(cumulative_cases.begin(), cumulative_cases.end());

    cout<<maximum;
    for(int i=0; i<194;i++)
    {
        double x = 255*static_cast<double>(cumulative_cases[i])/static_cast<double>(maximum);
        int color=255-round(x);
        if(cumulative_cases[i]>=0)
        {
            sprites[i].setColor(sf::Color(color,0,0));
        }
    }
    return sprites;
}


int main()
{




    vector <sf::Sprite > sprites;
    vector <string> countries;
    vector <int> cumulative_cases(194);

    vector <string> dateRep;
    vector <string> day;
    vector <string> month;
    vector <string> year;
    vector <int> cases;
    vector <string> deaths;
    vector <string> countriesAndTerritories;
    vector <string> geoId;
    vector <string> countryterritoryCode;
    vector <string> popData2019;
    vector <string> continentExp;
    vector <string> Cumulative_number_for_14_days;

    ifstream database;
    database.open("database");


    int mark = 1;
    while(database.good())
    {
        string line;
        getline(database, line, ',');
        if(mark==7)
        {
            countriesAndTerritories.push_back(line);
        }

        if(mark==5)
        {

            cases.push_back(atoi(line.c_str()));
        }




        mark++;
        if(mark==13)
        {
            mark=1;
        }
    }

    #include "countries.h"

    cumulative_cases= cumulative(countries, countriesAndTerritories, cases);
    sprites = cumulative_draw(sprites, cumulative_cases);
    cout<<cumulative_cases[193]<<endl;
    cout<<*max_element(cumulative_cases.begin(), cumulative_cases.end());



    sf::RenderWindow window(sf::VideoMode(1540, 700), "Covid-19 Map");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(135,206,235));





        for(int i=0;i<194;i++)
        {
            window.draw(sprites[i]);
        }

        window.display();


    }

    return 0;
}
