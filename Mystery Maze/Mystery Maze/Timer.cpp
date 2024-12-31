#include "Timer.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

Timer::Timer(float totalTime) : totalTime(totalTime), remainingTime(totalTime) {
    if (!timerFont.loadFromFile("fonts/joystix_monospace.otf")) {
        std::cerr << "Font file not found" << std::endl;
    }

    timerText.setFont(timerFont);
    timerText.setCharacterSize(40);
    timerText.setFillColor(sf::Color::White);
}

void Timer::update(const sf::RenderWindow& window) {
    float elapsed = tClock.getElapsedTime().asSeconds();
    remainingTime -= elapsed;
    tClock.restart();

    //update the timer text
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << remainingTime;
    timerText.setString(ss.str());

    //position the timer text based on the view
    const sf::View& view = window.getView();
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    float startX = viewCenter.x - viewSize.x / 2.f + 10.f;
    float startY = viewCenter.y - viewSize.y / 2.f + 40.f;

    timerText.setPosition(startX, startY);
}


void Timer::reset() {
    tClock.restart();//restart clock
    remainingTime = totalTime; //reset remaining time
}

float Timer::getRemainingTime() const {
    return remainingTime;
}

void Timer::setRemainingTime(float time) {
    if (time < 0.0f) {
        std::cerr << "Error: Invalid remaining time!" << std::endl;
        return;
    }
    remainingTime = time; 
    tClock.restart();     
}



void Timer::draw(sf::RenderWindow& window) {
    window.draw(timerText);
}
