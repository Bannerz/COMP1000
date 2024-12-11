#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Zombie {
public:
    Zombie(float movementSpeed, float animationSpeed); //zombie constructor
    void setPosition(float x, float y); //set zombie position
    void update(class Player& player, const sf::Vector2f& playerPosition, const std::vector<sf::Sprite>& wallSprites, float elapsedTime);
    void draw(sf::RenderWindow& window, const std::vector<std::vector<bool>>& fogGrid, int cellSize);

    static std::vector<Zombie> spawnZombies(int zombieCount, const sf::FloatRect& mapBounds, const std::vector<sf::Sprite>& wallSprites, const std::string& zombieTexturePath, float movementSpeed, float animationSpeed); //spawn zombies method

    sf::FloatRect getCollisionBounds() const { return collisionBox.getGlobalBounds(); } //get collision bounds

private:
    enum Direction { Right, Left, Down, Up }; //enumerate directions for later use

    static sf::Texture zombieTexture; //static texture shared across all zombies
    sf::Sprite sprite; //initialise sprite object
    sf::RectangleShape collisionBox; //initialise collision box object

    float movementSpeed; //initialise mov speed
    float animationSpeed; //initialise anim speed
    Direction currentDirection; //init current direction
    sf::Clock animationClock; //init clock for anim
    int frameState = 0; //set frame state
    int currentRow = 0; //set row of sprite

    Direction getRandomDirection(); //get random direction
    void updateCollisionBox(); //update collision
};

#endif
