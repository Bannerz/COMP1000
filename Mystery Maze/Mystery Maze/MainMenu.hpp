#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class MainMenu {
public:
    MainMenu(float width, float height);

    void draw(sf::RenderWindow& window); //draws the menu
    void MoveUp(); //move selection up
    void MoveDown(); //move selection down

    //returns the currently selected menu option
    int MainMenuPressed() const {
        return MainMenuSelected;
    }

    

    ~MainMenu();

private:
    static constexpr int Max_main_menu = 4; //number of menu items
    int MainMenuSelected = 0; //default selection is the first item
    sf::Font font; //font used for menu items
    sf::Text mainMenu[Max_main_menu]; //menu items array
};
