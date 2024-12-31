#include "Winner.hpp"
#include "MainMenu.hpp"
#include "Score.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

void Winner::runWinScreen(sf::RenderWindow& window, int playerScore) {

    if (!font.loadFromFile("fonts/joystix_monospace.otf")) {
        std::cout << "font not found" << std::endl;
    }

    sf::Text winText("Winner!", font, 70);
    winText.setFillColor(sf::Color::White);
    winText.setPosition(600, 600);

    sf::Text scoreText("Score: " + std::to_string(playerScore), font, 70);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(500, 700);

    sf::Text retText("Press 'Enter' to return to main menu.", font, 40);
    retText.setFillColor(sf::Color::White);
    retText.setPosition(250, 800);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) {
                return; //return to menu
            }
        }

        window.clear();
        window.draw(winText);
        window.draw(retText);
        window.draw(scoreText);
        window.display();



    }
}
