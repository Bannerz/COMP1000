#include "Potions.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include <algorithm>

using namespace std;

sf::Texture Potions::healthPotTexture; //define the static texture

int Potions::idCounter = 0;

Potions::Potions(const std::string& healthPotPath, int healthAdd)
    : healthAdd(healthAdd) {

    this->id = idCounter++;

    if (!healthPotTexture.loadFromFile(healthPotPath)) {
        std::cerr << "Error: Could not load potion texture: " << healthPotPath << std::endl;
    }
    else {
        std::cout << "Potion texture loaded successfully!" << std::endl;
    }    

    healthPotSprites.setTexture(healthPotTexture);
    healthPotSprites.setTextureRect(sf::IntRect(0, 0, 16, 16)); // Default frame
    healthPotSprites.setScale(1.f, 1.f);

    collisionBox.setSize(sf::Vector2f(16.f, 16.f)); // Match scaled sprite size
    collisionBox.setFillColor(sf::Color(255, 0, 0, 50)); // Debug red
}

void Potions::setPotPosition(float x, float y) {
    healthPotSprites.setPosition(x, y);
    collisionBox.setPosition(x, y); // Ensure collision box moves with sprite
}

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

        // Generate a random position within the map bounds
        float x = randomX(rng);
        float y = randomY(rng);

        // Create a temporary potion for collision checking
        Potions tempPotion(healthPotPath, 10); // 10 health added
        tempPotion.setPotPosition(x, y);

        // Check for collisions with walls
        bool collisionDetected = false;
        for (const auto& wall : wallSprites) {
            if (tempPotion.getCollisionBounds().intersects(wall.getGlobalBounds())) {
                collisionDetected = true;
                break;
            }
        }

        // If no collision, add the potion to the list
        if (!collisionDetected) {
            potions.push_back(tempPotion);
        }
    }

    if (potions.size() < potionCount) {
        std::cerr << "Warning: Could only spawn " << potions.size() << " potions out of " << potionCount << "." << std::endl;
    }

    return potions;
}

void Potions::update(Player& player) {
    if (isActive && getCollisionBounds().intersects(player.getCollisionBounds())) {
        // Heal the player
        if (player.playerHealth >= 48) {
            player.playerHealth = 48;
        }
        else if (player.playerHealth < 48) {
            player.playerHealth += healthAdd; // Add health to the player
            isActive = false; // Mark potion as inactive
           }
        
    }
}





void Potions::draw(sf::RenderWindow& window, const std::vector<std::vector<bool>>& fogGrid, int cellSize) {
    sf::Vector2f position = healthPotSprites.getPosition();
    int gridX = static_cast<int>(position.x / cellSize);
    int gridY = static_cast<int>(position.y / cellSize);


    if (gridY >= 0 && gridY < static_cast<int>(fogGrid.size()) &&
        gridX >= 0 && gridX < static_cast<int>(fogGrid[gridY].size())) {
        if (!fogGrid[gridY][gridX]) { // Tile is revealed
            window.draw(healthPotSprites);
            collisionBox.setFillColor(sf::Color(255, 0, 0, 100)); // Debug red
            window.draw(collisionBox);
        }
        else { // Tile is fogged
            collisionBox.setFillColor(sf::Color(255, 0, 0, 50)); // Dim red
            window.draw(collisionBox);
        }
    }
}
