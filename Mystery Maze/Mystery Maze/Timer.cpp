#include "Timer.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

Timer::Timer(float totalTime) : totalTime(totalTime), remainingTime(totalTime) {
    if (!timerFont.loadFromFile("fonts/joystix_monospace.otf")) {
        std::cerr << "No font file found!" << std::endl;
    }

    timerText.setFont(timerFont);
    timerText.setCharacterSize(40);
    timerText.setFillColor(sf::Color::White);
}

void Timer::update(const sf::RenderWindow& window) {
    //calculate the remaining time
    remainingTime = totalTime - tClock.getElapsedTime().asSeconds();
    if (remainingTime < 0) remainingTime = 0; //stop negative time

    //format the remaining time as seconds
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << remainingTime;
    timerText.setString("Time: " + ss.str());

    //update the position based on the view
    const sf::View& view = window.getView();
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    float startX = viewCenter.x - viewSize.x / 2.f + 10.f; //top left corner with padding
    float startY = viewCenter.y - viewSize.y / 2.f + 40.f; //padding of 40 below

    timerText.setPosition(startX, startY);
}

void Timer::reset() {
    tClock.restart();//restart clock
    remainingTime = totalTime; //reset remaining time
}

float Timer::getRemainingTime() const {
    return remainingTime;
}

void Timer::draw(sf::RenderWindow& window) {
    window.draw(timerText);
}
