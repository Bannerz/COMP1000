#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Options {
public:
   Options(float width, float height);

    void opDraw(sf::RenderWindow& window); // Draws the menu
    void opMoveUp(); // Move selection up
    void opMoveDown(); // Move selection down

    // Returns the currently selected menu option
    int OptionsPressed() const {
        return OptionsSelected;
    }



    ~Options();

private:
    static constexpr int Max_options_menu = 4; // Number of menu items
    int OptionsSelected = 0; // Default selection is the first item
    sf::Font font; // Font used for menu items
    sf::Text optionsMenu[Max_options_menu];
    void OptionsMenu();
    // Menu items array
};


