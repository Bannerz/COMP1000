#include "Credits.hpp"
#include "MainMenu.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

void Credits::runCredits(sf::RenderWindow& window) {

    if (!font.loadFromFile("fonts/joystix_monospace.otf")) {
        std::cout << "font not found" << std::endl;
    }

    sf::Text creditsText("Credits:\nGame developed by Alex Banfield \nSprites: \nCazWolf: https://cazwolf.itch.io/tiny-pixel-fantasy-generator \nChris Hamons: https://opengameart.org/content/dungeon-crawl-32x32-tiles \nTutorials Used: \nMenu Tutorial: YouTube.com/watch?v=bOG8667yePY \nScreen States:YouTube.com/watch?v=Qhlqhen6cmw \nViews Documentation: https://www.sfml-dev.org/tutorials/2.6/graphics-view.php \n \n Press 'Enter' to return to return to main menu.", font, 20);
    creditsText.setFillColor(sf::Color::White);
    creditsText.setPosition(100, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) {
                return; // Exit credits
            }
        }

        window.clear();
        window.draw(creditsText);
        window.display();



    }
}
