#pragma once
#include <SFML/Graphics.hpp>
class Score
{
private:
	sf::Font scoreFont;
	sf::Text scoreText;
	int playerScore;

public:
	Score(int initialScore = 0);
	void update(const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void scoreUp(int value);
	void setPlayerScore(int newScore);
	int getPlayerScore() const;
};

