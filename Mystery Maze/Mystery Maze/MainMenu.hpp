#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class MainMenu {
public:
    MainMenu(float width, float height);

    void draw(sf::RenderWindow& window); // Draws the menu
    void MoveUp(); // Move selection up
    void MoveDown(); // Move selection down

    // Returns the currently selected menu option
    int MainMenuPressed() const {
        return MainMenuSelected;
    }

    

    ~MainMenu();

private:
    static constexpr int Max_main_menu = 4; // Number of menu items
    int MainMenuSelected = 0; // Default selection is the first item
    sf::Font font; // Font used for menu items
    sf::Text mainMenu[Max_main_menu]; // Menu items array
};
