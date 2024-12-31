#pragma once
#include <SFML/Graphics.hpp>
class Timer
{
private:
    sf::Font timerFont;
    sf::Clock tClock;
    sf::Text timerText;

    float totalTime;//total countdown time in seconds
public:
    Timer(float totalTime); //initialise with total countdown time
    void update(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void reset();
    float remainingTime; //remaining time in seconds

    float getRemainingTime() const;
    void setRemainingTime(float time);
};

