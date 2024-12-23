#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Potions
{
public:
	Potions(const std::string& healthPotPath, int healthAdd);
	void setPotPosition(float x, float y); //set potion position
	void draw(sf::RenderWindow& window);


	int healthAdd;
private:
	sf::Texture healthPotTexture;
	sf::Sprite healthPotSprites;
};

