#include "Potions.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Potions::Potions(const std::string& healthPotPath, int healthAdd) {
    //ensure the texture is loaded
    if (healthPotTexture.getSize().x == 0) { //check if the texture is not loaded
        if (!healthPotTexture.loadFromFile("textures/items/healthPot.png")) {
            std::cerr << "Error: Could not load potion texture" << std::endl;
        }
        else {
            std::cout << "Potion texture loaded successfully!" << std::endl;
        }
    }

    healthPotSprites.setTexture(healthPotTexture);
    healthPotSprites.setTextureRect(sf::IntRect(0, 0, 16, 16)); // Default frame

    // sprite scale
    healthPotSprites.setScale(2.f, 2.f);
   
}

void Potions::setPotPosition(float x, float y) {
    healthPotSprites.setPosition(x, y);
    
}

void Potions::draw(sf::RenderWindow& window) {
    window.draw(healthPotSprites); //draw player sprite
  
}