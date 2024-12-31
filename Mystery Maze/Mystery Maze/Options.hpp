#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Options {
public:
   Options(float width, float height);

    void opDraw(sf::RenderWindow& window); //draws the menu
    void opMoveUp(); //move selection up
    void opMoveDown(); //move selection down

    //returns the currently selected menu option
    int OptionsPressed() const {
        return OptionsSelected;
    }



    ~Options();

private:
    static constexpr int Max_options_menu = 4; //number of menu items
    int OptionsSelected = 0; //default selection is the first item
    sf::Font font; //dont used for menu items
    sf::Text optionsMenu[Max_options_menu];
    void OptionsMenu();
};


