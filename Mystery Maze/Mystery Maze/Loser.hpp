#pragma once
#include <SFML/Graphics.hpp>

class Loser {
public:
	void runLoseScreen(sf::RenderWindow& window, int playerScore);
	void runOOT(sf::RenderWindow& window, int playerScore);

private:
	sf::Font font;

};

