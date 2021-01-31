#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include<windows.h>

#include "Button.cpp"



using namespace std;

vector <int> cumulative(vector <string> countries, vector <string> countriesAndTerritories, vector <double> cases )
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
    for(int i=0; i<194;i++)
    {
        double x = 255*cumulative_cases[i]/static_cast<double>(maximum);
        int red =round(x);
        int green =255- round(x);
        if(green<0)
        {
            green=0;
        }
        if(cumulative_cases[i]>=0)
        {
            sprites[i].setColor(sf::Color(0,green,0));
        }
    }
    return sprites;
}

vector <sf::Sprite > last14(vector <sf::Sprite > sprites, vector <double> last14_cases,vector <string> countriesAndTerritories , vector <int> day, vector <int> month, vector <int> year, int current_day, int current_month, int current_year, vector <string> countries)
{
    int day_size = static_cast<int>(day.size());

    for(int i=0; i<day_size;i++)
    {
        if(day[i] == current_day && month[i]== current_month && year[i] == current_year)
        {
            for(int y=0; y<194;y++)
            {
              if(countries[y] == countriesAndTerritories[i])
              {
                double x = (last14_cases[i])/700;
                int red =round(x);
                int green =round(255-255*x);
                if(green<0)
                {
                    green=0;
                }
                sprites[y].setColor(sf::Color(0,green,0));
                break;
              }
            }
        }
    }
    return sprites;
}

vector <sf::Sprite > daily(vector <sf::Sprite > sprites, vector <double> cases,vector <string> countriesAndTerritories , vector <int> day, vector <int> month, vector <int> year, int current_day, int current_month, int current_year, vector <string> countries, vector <double> popData2019 )
{

    int day_size = static_cast<int>(day.size());


    for(int i=0; i<day_size;i++)
    {
        if(day[i] == current_day && month[i]== current_month && year[i] == current_year)
        {
            for(int y=0; y<194;y++)
            {
              if(countries[y] == countriesAndTerritories[i])
              {
                double x = (100000*cases[i])/(popData2019[i])/50;
                int red =round(x);
                int green = round(255-255*x);
                if(green<0)
                {
                    green=0;
                }
                sprites[y].setColor(sf::Color(0,green,0));
                //cout<<endl<<x;
                break;
              }
            }
        }
    }
    return sprites;
}

vector <sf::Sprite > mortality(vector <sf::Sprite > sprites, vector <double> cases,vector <string> countriesAndTerritories , vector <int> day, vector <int> month, vector <int> year, int current_day, int current_month, int current_year, vector <string> countries, vector <double> deaths )
{

    int day_size = static_cast<int>(day.size());

    for(int i=0; i<day_size;i++)
    {
        if(day[i] == current_day && month[i]== current_month && year[i] == current_year)
        {
            for(int y=0; y<194;y++)
            {
              if(countries[y] == countriesAndTerritories[i])
              {
                if(cases[i]!=0)
                {
                double x = (100*deaths[i])/(cases[i])/10;
                int red =round(x);
                int green = round(255-255*x);
                if(green<0)
                {
                    green=0;
                }
                sprites[y].setColor(sf::Color(0,green,0));
                break;
                }
                else
                {
                    sprites[y].setColor(sf::Color(0,255,0));
                }
              }
            }
        }
    }
    return sprites;
}


int main()
{
    sf::RectangleShape bottom(sf::Vector2f(1750, 160));
    bottom.setPosition(0,740);
    bottom.setFillColor(sf::Color::Black);

    sf::RectangleShape hide_date(sf::Vector2f(650, 150));
    hide_date.setPosition(850,740);
    hide_date.setFillColor(sf::Color::Black);


    sf::Font arial;
    arial.loadFromFile("arial.ttf");

    sf::Text day_text;
    day_text.setFont(arial);
    day_text.setString("Day:");
    day_text.setCharacterSize(40);
    day_text.setFillColor(sf::Color::Red);
    day_text.setPosition(885,738);

    sf::Text month_text;
    month_text.setFont(arial);
    month_text.setString("Month:");
    month_text.setCharacterSize(40);
    month_text.setFillColor(sf::Color::Red);
    month_text.setPosition(1065,738);

    sf::Text year_text;
    year_text.setFont(arial);
    year_text.setString("Year:");
    year_text.setCharacterSize(40);
    year_text.setFillColor(sf::Color::Red);
    year_text.setPosition(1295,738);

    int current_day = 1;
    int current_month = 1;
    int current_year = 2020;

    sf::Text day_show;
    day_show.setFont(arial);
    day_show.setString( to_string(current_day));
    day_show.setCharacterSize(50);
    day_show.setFillColor(sf::Color::Red);
    day_show.setPosition(910,805);

    sf::Text month_show;
    month_show.setFont(arial);
    month_show.setString(to_string(current_month));
    month_show.setCharacterSize(50);
    month_show.setFillColor(sf::Color::Red);
    month_show.setPosition(1110,805);

    sf::Text year_show;
    year_show.setFont(arial);
    year_show.setString(to_string(current_year));
    year_show.setCharacterSize(50);
    year_show.setFillColor(sf::Color::Red);
    year_show.setPosition(1288,805);



    Button cumulative_button("All cases from 31/12/2019 to 30/11/2020", {400, 50}, 20, sf::Color::White, sf::Color::Black);
    cumulative_button.setFont(arial);
    cumulative_button.setPosition({440,830});

    Button last14_button("   Last 14 days cases per 100 000 people", {400, 50}, 20, sf::Color::White, sf::Color::Black);
    last14_button.setFont(arial);
    last14_button.setPosition({20,830});

    Button dailyper100_button("Daily cases per 100 000 people", {400, 50}, 20, sf::Color::White, sf::Color::Black);
    dailyper100_button.setFont(arial);
    dailyper100_button.setPosition({20,760});

    Button mortality_button("Daily mortality (cases/deaths)", {400, 50}, 20, sf::Color::White, sf::Color::Black);
    mortality_button.setFont(arial);
    mortality_button.setPosition({440,760});

    Button day_plus_button("+  ", {35, 35}, 19, sf::Color::White, sf::Color::Black);
    day_plus_button.setFont(arial);
    day_plus_button.setPosition({1000,790});

    Button day_minus_button("-  ", {35, 35}, 16, sf::Color::White, sf::Color::Black);
    day_minus_button.setFont(arial);
    day_minus_button.setPosition({1000,845});

    Button month_plus_button("+  ", {35, 35}, 19, sf::Color::White, sf::Color::Black);
    month_plus_button.setFont(arial);
    month_plus_button.setPosition({1220,790});

    Button month_minus_button("-  ", {35, 35}, 16, sf::Color::White, sf::Color::Black);
    month_minus_button.setFont(arial);
    month_minus_button.setPosition({1220,845});

    Button year_plus_button("+  ", {35, 35}, 19, sf::Color::White, sf::Color::Black);
    year_plus_button.setFont(arial);
    year_plus_button.setPosition({1430,790});

    Button year_minus_button("-  ", {35, 35}, 16, sf::Color::White, sf::Color::Black);
    year_minus_button.setFont(arial);
    year_minus_button.setPosition({1430,845});




    vector <sf::Sprite > sprites;
    vector <string> countries;
    vector <int> cumulative_cases(194);

    vector <string> dateRep;
    vector <int> day;
    vector <int> month;
    vector <int> year;
    vector <double> cases;
    vector <double> deaths;
    vector <string> countriesAndTerritories;
    vector <string> geoId;
    vector <string> countryterritoryCode;
    vector <double> popData2019;
    vector <string> continentExp;
    vector <double> Cumulative_number_for_14_days;
    int month_days[12] ={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int last14_state=0;
    int cumulative_state=0;
    int daily_state=0;
    int mortality_state=0;

    ifstream database;
    database.open("database");

//vector <sf::Sprite > last14(vector <sf::Sprite > sprites, vector <float> last14_cases, vector <int> day, vector <int> month, vector <int> year, int current_day, int current_month, int current_year)
  //(sprites, Cumulative_number_for_14_days, day, month, year, current_day, current_month, current_year)
    int mark = 1;
    while(database.good())
    {
        string line;
        getline(database, line, ',');

        if(mark==1)
        {
            dateRep.push_back(line);
        }

        if(mark==2)
        {

            day.push_back(atoi(line.c_str()));
        }

        if(mark==3)
        {

            month.push_back(atoi(line.c_str()));
        }

        if(mark==4)
        {

            year.push_back(atoi(line.c_str()));
        }

        if(mark==5)
        {

            cases.push_back(atof(line.c_str()));
        }

        if(mark==6)
        {

            deaths.push_back(atof(line.c_str()));
        }

        if(mark==7)
        {
            countriesAndTerritories.push_back(line);
        }

        if(mark==10)
        {
            if(line=="")
            {
                line="0";
            }

            popData2019.push_back(atof(line.c_str()));
        }


        if(mark==12)
        {

            Cumulative_number_for_14_days.push_back(atof(line.c_str()));
        }



        mark++;
        if(mark==13)
        {
            mark=1;
        }
    }

    #include "countries.h"

    cumulative_cases= cumulative(countries, countriesAndTerritories, cases);
    //sprites = cumulative_draw(sprites, cumulative_cases);
    cout<<cumulative_cases[193]<<endl;
    cout<<*max_element(cumulative_cases.begin(), cumulative_cases.end());



    sf::RenderWindow window(sf::VideoMode(1500, 900), "Covid-19 Map"); //1500x740
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            switch (event.type)
            {
                case sf::Event::MouseButtonPressed:
                    if (cumulative_button.isMouseOver(window))
                    {
                        cumulative_state=1;
                        last14_state=0;
                        daily_state=0;
                        mortality_state=0;
                    }

                case sf::Event::MouseMoved:
                    if (cumulative_button.isMouseOver(window) || cumulative_state==1)
                    {
                        cumulative_button.setBackColor(sf::Color::Green);
                    }

                    else if (cumulative_state==1)
                    {
                        cumulative_button.setBackColor(sf::Color::Green);
                    }


                    else
                    {
                        cumulative_button.setBackColor(sf::Color::White);
                    }
                    break;


            }

            switch (event.type)
            {
                case sf::Event::MouseButtonPressed:
                    if (last14_button.isMouseOver(window))
                    {
                        last14_state=1;
                        cumulative_state=0;
                        daily_state=0;
                        mortality_state=0;
                    }

                case sf::Event::MouseMoved:
                    if (last14_button.isMouseOver(window) || last14_state==1)
                    {
                        last14_button.setBackColor(sf::Color::Green);
                    }

                    else if (last14_state==1)
                    {
                        last14_button.setBackColor(sf::Color::Green);
                    }

                    else
                    {
                        last14_button.setBackColor(sf::Color::White);
                    }
                    break;


            }

            switch (event.type)
            {

                case sf::Event::MouseButtonPressed:
                    if (dailyper100_button.isMouseOver(window))
                    {
                        daily_state=1;
                        cumulative_state=0;
                        last14_state=0;
                        mortality_state=0;
                    }

                case sf::Event::MouseMoved:
                    if (dailyper100_button.isMouseOver(window) || daily_state==1)
                    {
                        dailyper100_button.setBackColor(sf::Color::Green);
                    }

                    else if (daily_state==1)
                    {
                        dailyper100_button.setBackColor(sf::Color::Green);
                    }

                    else
                    {
                        dailyper100_button.setBackColor(sf::Color::White);
                    }
                    break;


            }

            switch (event.type)
            {
                    case sf::Event::MouseButtonPressed:
                    if (mortality_button.isMouseOver(window))
                    {
                        mortality_state=1;
                        daily_state=0;
                        cumulative_state=0;
                        last14_state=0;
                    }

                case sf::Event::MouseMoved:
                    if (mortality_button.isMouseOver(window))
                    {
                        mortality_button.setBackColor(sf::Color::Green);
                    }

                    else if (mortality_state==1)
                    {
                        mortality_button.setBackColor(sf::Color::Green);
                    }

                    else
                    {
                        mortality_button.setBackColor(sf::Color::White);
                    }
                    break;


            }

            switch (event.type)
            {
                case sf::Event::MouseMoved:
                    if (day_plus_button.isMouseOver(window))
                    {
                        day_plus_button.setBackColor(sf::Color::Green);
                    }

                    else
                    {
                        day_plus_button.setBackColor(sf::Color::White);
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    if (day_plus_button.isMouseOver(window))
                    {
                        if(current_year==2019 && current_month==12 && current_day==31)
                        {
                            current_year=2020;
                            current_month=1;
                            current_day=0;
                        }
                        current_day++;
                    }

            }

            switch (event.type)
            {
                case sf::Event::MouseMoved:
                    if (day_minus_button.isMouseOver(window))
                    {
                        day_minus_button.setBackColor(sf::Color::Green);
                    }

                    else
                    {
                        day_minus_button.setBackColor(sf::Color::White);
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    if (day_minus_button.isMouseOver(window))
                    {
                        current_day--;
                    }

            }

            switch (event.type)
            {
                case sf::Event::MouseMoved:
                    if (month_plus_button.isMouseOver(window))
                    {
                        month_plus_button.setBackColor(sf::Color::Green);
                    }

                    else
                    {
                        month_plus_button.setBackColor(sf::Color::White);
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    if (month_plus_button.isMouseOver(window))
                    {
                        current_month++;
                        if(current_day>month_days[current_month-1])
                        {
                            current_day=month_days[current_month-1];
                        }
                    }

            }

            switch (event.type)
            {
                case sf::Event::MouseMoved:
                    if (month_minus_button.isMouseOver(window))
                    {
                        month_minus_button.setBackColor(sf::Color::Green);
                    }

                    else
                    {
                        month_minus_button.setBackColor(sf::Color::White);
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    if (month_minus_button.isMouseOver(window))
                    {
                        current_month--;
                        if(current_day>month_days[current_month-1])
                        {
                            current_day=month_days[current_month-1];
                        }

                    }

            }

            switch (event.type)
            {
                case sf::Event::MouseMoved:
                    if (year_plus_button.isMouseOver(window))
                    {
                        year_plus_button.setBackColor(sf::Color::Green);
                    }

                    else
                    {
                        year_plus_button.setBackColor(sf::Color::White);
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    if (year_plus_button.isMouseOver(window))
                    {
                        current_year++;
                    }

            }

            switch (event.type)
            {
                case sf::Event::MouseMoved:
                    if (year_minus_button.isMouseOver(window))
                    {
                        year_minus_button.setBackColor(sf::Color::Green);
                    }

                    else
                    {
                        year_minus_button.setBackColor(sf::Color::White);
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    if (year_minus_button.isMouseOver(window))
                    {
                        current_year--;
                    }

            }





        }
        window.clear(sf::Color(135,206,235));




        if(current_year%4==0)
        {
            month_days[1]=29;
        }

        else
        {
            month_days[1]=28;
        }


        if(current_month>12)
        {
            current_year++;
            current_month=1;
        }

        if(current_month<1)
        {
            current_year--;
            current_month=12;
        }

        if(current_day>month_days[current_month-1])
        {

                current_month++;
                current_day=1;

        }

        if(current_year>2020)
        {
            current_year=2020;
            current_month=11;
            current_day=30;
        }

        if(current_month==1 && current_day<=0)
        {

            current_year--;
            current_month=12;
            current_day = 31;

        }

        if(current_month!=1 && current_day<=0)
        {
            current_month--;
            current_day=month_days[current_month-1];

        }

        if(current_year<2019)
        {
            current_year=2019;
        }

        if(current_year==2019)
        {
            current_day=31;
            current_month=12;
        }

        if(current_year==2020 && current_month>11)
        {
            current_year=2020;
            current_month=11;
            current_day=30;
        }

        for(int i=0;i<194;i++)
        {
            sprites[i].setColor(sf::Color(220,220,220));
            window.draw(sprites[i]);
        }

        if(cumulative_state==1)
        {
            sprites = cumulative_draw(sprites, cumulative_cases);
        }

        if(last14_state==1)
        {
            sprites = last14(sprites, Cumulative_number_for_14_days, countriesAndTerritories, day, month, year, current_day, current_month, current_year, countries);
        }

        if(daily_state==1)
        {
            sprites = daily(sprites, cases, countriesAndTerritories, day, month, year, current_day, current_month, current_year, countries, popData2019);
        }

        if(mortality_state==1)
        {
            sprites = mortality(sprites, cases, countriesAndTerritories, day, month, year, current_day, current_month, current_year, countries, deaths);
        }



        for(int i=0;i<194;i++)
        {
            window.draw(sprites[i]);
        }



        window.draw(background);

        window.draw(bottom);

        cumulative_button.drawTo(window);

        last14_button.drawTo(window);

        dailyper100_button.drawTo(window);

        mortality_button.drawTo(window);

        day_plus_button.drawTo(window);

        day_minus_button.drawTo(window);

        month_plus_button.drawTo(window);

        month_minus_button.drawTo(window);

        year_plus_button.drawTo(window);

        year_minus_button.drawTo(window);

        window.draw(day_text);

        window.draw(month_text);

        window.draw(year_text);

        window.draw(day_show);

        window.draw(month_show);

        window.draw(year_show);

        day_show.setString( to_string(current_day));

        month_show.setString( to_string(current_month));

        year_show.setString( to_string(current_year));

        if(cumulative_state==1)
        {
            window.draw(hide_date);
        }





        window.display();
        Sleep(50);



    }

    return 0;
}
