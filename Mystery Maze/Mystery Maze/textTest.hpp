#pragma once
#include <SFML/Graphics.hpp>


class textTest
{
public:
	textTest(float x, float y);
	void runTextTest(sf::RenderWindow& window);

private:
	sf::Font font;
	int test;
};

