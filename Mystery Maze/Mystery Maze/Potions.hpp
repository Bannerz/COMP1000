#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Potions
{
public:

	static int idCounter; //static counter for generating unique ids
	int id;  //unique ID for each potion

	Potions(const std::string& healthPotPath, int healthAdd); //potions constructor

	void setPotPosition(float x, float y); //set potion position
	void draw(sf::RenderWindow& window, const std::vector<std::vector<bool>>& fogGrid, int cellSize); //draw function
	void update(class Player& player); //update state function

	static std::vector<Potions> spawnPotions(int potionCount, const sf::FloatRect& mapBounds, const std::vector<sf::Sprite>& wallSprites, const std::string& healthPotPath); //spawn potions method

	sf::FloatRect getCollisionBounds() const { return collisionBox.getGlobalBounds(); } //get collision bounds

	bool shouldDespawn() const { return !isActive; } //despawn if inactive (player used)

	int healthAdd = 0;
	bool isActive = true; //tracks if the potion is active or should be despawned, set to true until player interacts

private:
	static sf::Texture healthPotTexture; //static texture shared across all health potions
	sf::Sprite healthPotSprites;
	sf::RectangleShape collisionBox; //initialise collision box object
};

