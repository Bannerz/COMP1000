#pragma once
#include <SFML/Graphics.hpp>

class Winner {
public:
	void runWinScreen(sf::RenderWindow& window, int playerScore);

private:
	sf::Font font;

};
