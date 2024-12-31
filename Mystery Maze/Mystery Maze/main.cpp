#include <SFML/Graphics.hpp>
#include "MainMenu.hpp"
#include "Credits.hpp"
#include "Game.hpp" 
#include "Options.hpp"
#include "textTest.hpp"
#include <iostream>

//define the GameState enum
enum GameState {
    MENU,
    PLAY,
    OPTIONS,
    CREDITS,
    EXIT
};

int main() {
    //create main window
    sf::RenderWindow window(sf::VideoMode(1600, 1600), "Mystery Maze", sf::Style::Default);

    Credits credits;
   

    //load and set window icon
    sf::Image icon;
    if (!icon.loadFromFile("textures/ui/icon.png")) {
        std::cerr << "Error: Could not load icon" << std::endl;
        return -1;
    }
    window.setIcon(16, 16, icon.getPixelsPtr());

    //initialise MainMenu
    MainMenu mainMenu(window.getSize().x, window.getSize().y);
    Options optionsMenu(window.getSize().x, window.getSize().y);
    textTest textTest(window.getSize().x, window.getSize().y);


    sf::FloatRect mapBounds(0.f, 0.f, 1600.f, 1600.f); //map bounds

    //track the current game state
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
                        case 0: //play
                            currentState = PLAY;
                            break;
                        case 1: //options
                            currentState = OPTIONS;
                            break;
                        case 2: //credits
                            currentState = CREDITS;
                            break;
                        case 3: //exit
                            window.close();
                            break;
                        }
                    }
                }
            }
            else if (currentState == OPTIONS) {
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Up) {
                        optionsMenu.opMoveUp(); //move selection up
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        optionsMenu.opMoveDown(); //move selection down
                    }
                    else if (event.key.code == sf::Keyboard::Return) {
                        int selectedOpOption = optionsMenu.OptionsPressed();
                        switch (selectedOpOption) {
                        case 0: //play
                            //textTest.runTextTest();
                            break;
                        case 1: //options
                            std::cout << "Option 2 Activated" << std::endl;
                            break;
                        case 2: //credits
                            std::cout << "Option 3 Activated" << std::endl;
                            break;
                        case 3: //exit
                            std::cout << "options closed" << std::endl;
                            currentState = MENU;
                            break;
                        }
                        
                    }
                }
            }
        }

        //clear the window
        window.clear();

        //render based on the current state
        if (currentState == MENU) {

            mainMenu.draw(window);

        }
        else if (currentState == PLAY) {
            //run game logic
            runGame(window); //call the function in game.cpp
            currentState = MENU; //return to main menu after game
        }
        else if (currentState == OPTIONS) {
            //render the Options menu
            optionsMenu.opDraw(window);
        }
        else if (currentState == CREDITS) {
            //run credits
            credits.runCredits(window); //call the function from Credits.cpp
            currentState = MENU; //return to main menu after credits
        }

        //display the window
        window.display();
    }

    return 0;
}
