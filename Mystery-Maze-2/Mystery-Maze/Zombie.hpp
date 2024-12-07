#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include <vector>
#include <string>

class Zombie {
public:
    enum Direction { Up, Down, Left, Right };

    Zombie(const std::string& zombieTexturePath, float movementSpeed, float animationSpeed);
    void setPosition(float x, float y);
    void update(Player& player, const sf::Vector2f& playerPosition, const std::vector<sf::Sprite>& wallSprites, float elapsedTime);
    void draw(sf::RenderWindow& window);
    void spawnZombies(std::vector<Zombie>& zombies, const std::string& zombieTexturePath, int zombieCount);

    sf::FloatRect getCollisionBounds() const { return collisionBox.getGlobalBounds(); }

private:
    void updateCollisionBox();
    Direction getRandomDirection();

    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape collisionBox;

    float movementSpeed;
    float animationSpeed;
    Direction currentDirection;
    int currentRow;  // Current animation row
    int frameState;  // Current frame state for animation
    sf::Clock animationClock;
};

#endif
