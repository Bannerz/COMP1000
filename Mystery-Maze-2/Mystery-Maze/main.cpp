#include <SFML/Graphics.hpp>
#include "MainMenu.hpp"
#include "Credits.hpp" // Incliude Credits logic header
#include "Game.hpp" // Include game logic header
#include "Options.hpp"
#include <iostream>

// Define the GameState enum
enum GameState {
    MENU,
    PLAY,
    OPTIONS,
    CREDITS,
    EXIT
};

int main() {
    // Create main window
    sf::RenderWindow window(sf::VideoMode(1600, 1600), "Mystery Maze", sf::Style::Default);

    Credits credits;
   

    // Load and set window icon
    sf::Image icon;
    if (!icon.loadFromFile("textures/ui/icon.png")) {
        std::cerr << "Error: Could not load icon" << std::endl;
        return -1;
    }
    window.setIcon(16, 16, icon.getPixelsPtr());

    // Initialize MainMenu
    MainMenu mainMenu(window.getSize().x, window.getSize().y);
    Options optionsMenu(window.getSize().x, window.getSize().y);


    sf::FloatRect mapBounds(0.f, 0.f, 1600.f, 1600.f); // Adjust as per your map size

    // Track the current game state
    GameState currentState = MENU;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (currentState == MENU) {
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Up) {
                        mainMenu.MoveUp();
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        mainMenu.MoveDown();
                    }
                    else if (event.key.code == sf::Keyboard::Return) {
                        int selectedOption = mainMenu.MainMenuPressed();
                        switch (selectedOption) {
                        case 0: // Play
                            currentState = PLAY;
                            break;
                        case 1: // Options
                            currentState = OPTIONS;
                            break;
                        case 2: // Credits
                            currentState = CREDITS;
                            break;
                        case 3: // Exit
                            window.close();
                            break;
                        }
                    }
                }
            }
            else if (currentState == OPTIONS) {
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Up) {
                        optionsMenu.opMoveUp(); // Move selection up
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        optionsMenu.opMoveDown(); // Move selection down
                    }
                    else if (event.key.code == sf::Keyboard::Return) {
                        int selectedOpOption = optionsMenu.OptionsPressed();
                        switch (selectedOpOption) {
                        case 0: // Play
                            std::cout << "Option 1 Activated" << std::endl;
                            break;
                        case 1: // Options
                            std::cout << "Option 2 Activated" << std::endl;
                            break;
                        case 2: // Credits
                            std::cout << "Option 3 Activated" << std::endl;
                            break;
                        case 3: // Exit
                            std::cout << "options closed" << std::endl;
                            currentState = MENU;
                            break;
                        }
                        
                    }
                }
            }
        }

        // Clear the window
        window.clear();

        // Render based on the current state
        if (currentState == MENU) {

            mainMenu.draw(window);

        }
        else if (currentState == PLAY) {
            // Run game logic
            runGame(window); // Call the function in game.cpp
            currentState = MENU; // Return to main menu after game
        }
        else if (currentState == OPTIONS) {
            // Render the Options menu
            optionsMenu.opDraw(window);
        }
        else if (currentState == CREDITS) {
            // Run credits
            credits.runCredits(window); // Call the function from Credits.cpp
            currentState = MENU; // Return to main menu after credits
        }

        // Display the contents of the window
        window.display();
    }

    return 0;
}
