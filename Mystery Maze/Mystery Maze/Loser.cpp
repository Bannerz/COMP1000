#include "Loser.hpp"
#include "MainMenu.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

void Loser::runLoseScreen(sf::RenderWindow& window, int playerScore) {

    if (!font.loadFromFile("fonts/joystix_monospace.otf")) {
        std::cout << "font not found" << std::endl;
    }

    sf::Text loseText("You lost!", font, 70);
    loseText.setFillColor(sf::Color::White);
    loseText.setPosition(600, 600);

    sf::Text scoreText("Score: " + std::to_string(playerScore), font, 70);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(500, 700);

    sf::Text retText("Press 'Enter' return to main menu.", font, 40);
    retText.setFillColor(sf::Color::White);
    retText.setPosition(250, 800);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) {
                return; //exit credits
            }
        }

        window.clear();
        window.draw(loseText);
        window.draw(scoreText);
        window.draw(retText);
        window.display();
    }
}

void Loser::runOOT(sf::RenderWindow& window, int playerScore) {

    if (!font.loadFromFile("fonts/joystix_monospace.otf")) {
        std::cout << "font not found" << std::endl;
    }

    sf::Text OOTText("You ran out of time!", font, 70);
    OOTText.setFillColor(sf::Color::White);
    OOTText.setPosition(220, 600);

    sf::Text scoreText("Score: " + std::to_string(playerScore), font, 70);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(500, 700);

    sf::Text retText("Press 'Enter' return to main menu.", font, 40);
    retText.setFillColor(sf::Color::White);
    retText.setPosition(250, 800);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) {
                return; //exit credits
            }
        }

        window.clear();
        window.draw(OOTText);
        window.draw(scoreText);
        window.draw(retText);
        window.display();
    }
}

