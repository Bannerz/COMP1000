#include "Potions.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include <algorithm>

using namespace std;

sf::Texture Potions::healthPotTexture; //define the static texture to avoid white box bug

int Potions::idCounter = 0; //set the id counter

Potions::Potions(const std::string& healthPotPath, int healthAdd)
    : healthAdd(healthAdd) {

    this->id = idCounter++; //increment idCounter

    //load texture and error handle
    if (!healthPotTexture.loadFromFile(healthPotPath)) {
        std::cerr << "Error: Could not load potion texture: " << healthPotPath << std::endl;
    }

    healthPotSprites.setTexture(healthPotTexture); //set texture
    healthPotSprites.setTextureRect(sf::IntRect(0, 0, 16, 16)); //set texture coords
    healthPotSprites.setScale(1.f, 1.f); //set sprite scale

    collisionBox.setSize(sf::Vector2f(16.f, 16.f)); //match scaled sprite size
    collisionBox.setFillColor(sf::Color(255, 0, 0, 50)); //debug red
}

//set position function
void Potions::setPotPosition(float x, float y) {
    healthPotSprites.setPosition(x, y); //set the position of the potion
    collisionBox.setPosition(x, y); //set the colliison box to match the potion
}

//spawn potions (similar to zombies)
std::vector<Potions> Potions::spawnPotions(
    int potionCount, const sf::FloatRect& mapBounds,
    const std::vector<sf::Sprite>& wallSprites, const std::string& healthPotPath) {

    std::vector<Potions> potions;
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> randomX(mapBounds.left, mapBounds.left + mapBounds.width);
    std::uniform_real_distribution<float> randomY(mapBounds.top, mapBounds.top + mapBounds.height);

    int attempts = 0;
    while (potions.size() < potionCount && attempts < potionCount * 10) {
        attempts++;

        //generate a random position in the map bounds
        float x = randomX(rng);
        float y = randomY(rng);

        //create a temporary potion for collision checking
        Potions tempPotion(healthPotPath, 10);
        tempPotion.setPotPosition(x, y);

        //check for collisions with walls
        bool collisionDetected = false;
        for (const auto& wall : wallSprites) {
            if (tempPotion.getCollisionBounds().intersects(wall.getGlobalBounds())) {
                collisionDetected = true;
                break;
            }
        }

        //if no collision, add the potion to the list
        if (!collisionDetected) {
            potions.push_back(tempPotion);
        }
    }

    //error handle
    if (potions.size() < potionCount) {
        std::cerr << "Warning: Could only spawn " << potions.size() << " potions out of " << potionCount << "." << std::endl;
    }

    return potions;
}

//update the potion states
void Potions::update(Player& player) {
    //if the potion is active and the collides with player
    if (isActive && getCollisionBounds().intersects(player.getCollisionBounds())) {
        //heal the player
        //if the player health is above 48 (width of the texture) reset to 48
        if (player.playerHealth >= 48) {
            player.playerHealth = 48;
        }
        //if the player health is below 48, increase the health and set the active flag to false to remove the potion
        else if (player.playerHealth < 48) {
            player.playerHealth += healthAdd; //add health to the player
            isActive = false; //mark potion as inactive
        }
    }
}

//draw potions
void Potions::draw(sf::RenderWindow& window, const std::vector<std::vector<bool>>& fogGrid, int cellSize) {
    sf::Vector2f position = healthPotSprites.getPosition();
    int gridX = static_cast<int>(position.x / cellSize);
    int gridY = static_cast<int>(position.y / cellSize);

    if (gridY >= 0 && gridY < static_cast<int>(fogGrid.size()) &&
        gridX >= 0 && gridX < static_cast<int>(fogGrid[gridY].size())) {
        if (!fogGrid[gridY][gridX]) { //tile is revealed
            window.draw(healthPotSprites);
            collisionBox.setFillColor(sf::Color(255, 0, 0, 100)); //debug red
            window.draw(collisionBox);
        }
        else { //tile is fogged
            collisionBox.setFillColor(sf::Color(255, 0, 0, 50)); //dim red for if under fog 
            window.draw(collisionBox);
        }
    }
}
