#include "Score.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

Score::Score(int initialScore) : playerScore(initialScore) {
    if (!scoreFont.loadFromFile("fonts/joystix_monospace.otf")) {
        std::cerr << "Font file not found" << std::endl;
        exit(EXIT_FAILURE);
    }
    scoreText.setFont(scoreFont);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Score: " + std::to_string(playerScore));
}

void Score::update(const sf::RenderWindow& window) {
   std::stringstream ss;
   ss << std::fixed << std::setprecision(0) << playerScore;
   scoreText.setString("Score: " + ss.str());

    //update the position based on the view
    const sf::View& view = window.getView();
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    float startX = viewCenter.x - viewSize.x / 2.f + 10.f; //top left corner with padding
    float startY = viewCenter.y - viewSize.y / 2.f + 80.f; //padding of 40 below

    scoreText.setPosition(startX, startY);
}

void Score::scoreUp(int value) {
    playerScore += value;
}

int Score::getPlayerScore() const {
    return playerScore;
}

void Score::setPlayerScore(int newScore) {
    playerScore = newScore;
    scoreText.setString("Score: " + std::to_string(playerScore));
}

void Score::draw(sf::RenderWindow& window) {
    window.draw(scoreText);
}