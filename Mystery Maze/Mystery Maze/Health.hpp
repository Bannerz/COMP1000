#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Health {
private:
    sf::Texture healthTexture;
    std::vector<sf::Sprite> heartSprites;

public:
    Health(const std::string& healthTexPath);
    void setLives(int playerLives);               //adjust hearts based on lives
    void updatePosition(const sf::RenderWindow& window); //reposition relative to the view
    void draw(sf::RenderWindow& window);          //draw all hearts
};
