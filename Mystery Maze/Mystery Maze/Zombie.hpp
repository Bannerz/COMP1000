#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Zombie {
public:
    // Existing methods
    Zombie(float movementSpeed, float animationSpeed);
    void setPosition(float x, float y);
    void update(class Player& player, const sf::Vector2f& playerPosition, const std::vector<sf::Sprite>& wallSprites, float elapsedTime);
    void draw(sf::RenderWindow& window, const std::vector<std::vector<bool>>& fogGrid, int cellSize);

    static std::vector<Zombie> spawnZombies(
        int zombieCount,
        const sf::FloatRect& mapBounds,
        const std::vector<sf::Sprite>& wallSprites,
        const std::string& zombieTexturePath,
        float movementSpeed,
        float animationSpeed);

    sf::FloatRect getCollisionBounds() const { return collisionBox.getGlobalBounds(); }

private:
    enum Direction { Right, Left, Down, Up };

    static sf::Texture zombieTexture; // Static texture shared across all zombies
    sf::Sprite sprite;
    sf::RectangleShape collisionBox;

    float movementSpeed;
    float animationSpeed;
    Direction currentDirection;
    sf::Clock animationClock;
    int frameState = 0;
    int currentRow = 0;

    Direction getRandomDirection();
    void updateCollisionBox();
};

#endif
