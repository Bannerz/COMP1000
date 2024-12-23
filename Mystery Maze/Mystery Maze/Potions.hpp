#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Potions
{
public:

	static int idCounter; // Static counter for generating unique ids
	int id;  // Unique ID for each potion

	Potions(const std::string& healthPotPath, int healthAdd);
	void setPotPosition(float x, float y); //set potion position
	void draw(sf::RenderWindow& window, const std::vector<std::vector<bool>>& fogGrid, int cellSize);
	void update(class Player& player);

	static std::vector<Potions> spawnPotions(int potionCount, const sf::FloatRect& mapBounds, const std::vector<sf::Sprite>& wallSprites, const std::string& healthPotPath); //spawn zombies method

	sf::FloatRect getCollisionBounds() const { return collisionBox.getGlobalBounds(); } //get collision bounds

	bool shouldDespawn() const { return !isActive; } // Despawn if inactive

	int healthAdd = 0;
	bool isActive = true; // Tracks if the potion is active or should be despawned

	

private:
	static sf::Texture healthPotTexture; //static texture shared across all zombies
	sf::Sprite healthPotSprites;
	sf::RectangleShape collisionBox; //initialise collision box object


};

