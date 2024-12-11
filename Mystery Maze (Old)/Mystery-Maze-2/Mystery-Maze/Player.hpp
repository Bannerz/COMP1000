#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Player {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape collisionBox;
   

    float animationSpeed;
    float movementSpeed;
    int frameState;
    int currentRow;

    sf::Clock animationClock;

    void updateCollisionBox();
    void updateHealthBar();

public:
    Player(const std::string& texturePath, float animationSpeed, float movementSpeed);
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::FloatRect getCollisionBounds() const;

    sf::RectangleShape healthBar;
    float playerHealth;
    
    void reduceHealth();

    void handleInput(float elapsedTime, const std::vector<sf::Sprite>& wallSprites);
    void draw(sf::RenderWindow& window);
    void health(float playerHealth);
};

#endif
