#include "Zombie.hpp"
#include "Player.hpp"
#include <cmath>
#include <random>
#include <iostream> // For debugging

using namespace std;

Zombie::Zombie(const std::string& zombieTexturePath, float movementSpeed, float animationSpeed)
    : movementSpeed(movementSpeed), animationSpeed(animationSpeed), currentDirection(getRandomDirection()) {
    if (!texture.loadFromFile(zombieTexturePath)) {
        std::cerr << "Error loading zombie texture from: " << zombieTexturePath << std::endl;
    }
    else {
        std::cout << "Zombie texture loaded successfully!" << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 48, 48));  // Adjust this based on your sprite sheet
    sprite.setScale(1.f, 1.f); // Set sprite scale

    collisionBox.setSize(sf::Vector2f(14.f, 14.f)); // Collision box size
    collisionBox.setFillColor(sf::Color(255, 0, 0, 100)); // Semi-transparent red for debugging
    collisionBox.setOrigin(-17.f, -30.f); // Adjust origin if necessary
}

void Zombie::setPosition(float x, float y) {
    sprite.setPosition(x, y);
    updateCollisionBox();
}

void Zombie::updateCollisionBox() {
    collisionBox.setPosition(sprite.getPosition());
}

Zombie::Direction Zombie::getRandomDirection() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> randomDirection(0, 3);
    return static_cast<Direction>(randomDirection(rng));
}

void Zombie::update(Player& player, const sf::Vector2f& playerPosition, const std::vector<sf::Sprite>& wallSprites, float elapsedTime) {
    sf::Vector2f movement(0.f, 0.f); // Initial movement vector
    float distanceToPlayer = std::hypot(sprite.getPosition().x - playerPosition.x,
        sprite.getPosition().y - playerPosition.y);

    int movement_mult = 6;
    bool isMoving;

    if (distanceToPlayer < 200.f) { // Detection radius
        sf::Vector2f targetDirection = playerPosition - sprite.getPosition();
        targetDirection /= std::hypot(targetDirection.x, targetDirection.y); // Normalize the vector

        sf::Vector2f potentialMovements[4] = {
            {movementSpeed * movement_mult, 0.f},  // Right
            {-movementSpeed * movement_mult, 0.f}, // Left
            {0.f, movementSpeed * movement_mult},  // Down
            {0.f, -movementSpeed * movement_mult}  // Up
        };

        int priority[4] = { 0, 1, 2, 3 }; // Indices of potentialMovements
        std::sort(priority, priority + 4, [&](int a, int b) {
            sf::Vector2f moveA = potentialMovements[a];
            sf::Vector2f moveB = potentialMovements[b];
            sf::Vector2f posA = sprite.getPosition() + moveA;
            sf::Vector2f posB = sprite.getPosition() + moveB;
            float distA = std::hypot(posA.x - playerPosition.x, posA.y - playerPosition.y);
            float distB = std::hypot(posB.x - playerPosition.x, posB.y - playerPosition.y);
            return distA < distB; // Closer directions are prioritized
            });

        bool pathFound = false;
        for (int i = 0; i < 4; ++i) {
            sf::Vector2f testMovement = potentialMovements[priority[i]];
            sf::FloatRect nextBounds = collisionBox.getGlobalBounds();
            nextBounds.left += testMovement.x;
            nextBounds.top += testMovement.y;

            bool collisionDetected = false;
            for (const auto& wall : wallSprites) {
                if (wall.getGlobalBounds().intersects(nextBounds)) {
                    collisionDetected = true;
                    break;
                }
            }

            if (!collisionDetected) {
                movement += testMovement;
                pathFound = true;
                break;
            }
        }

        if (!pathFound) {
            movement = sf::Vector2f(0.f, 0.f); // No direct path available, stop movement temporarily
        }

        // Determine animation row based on movement
        if (movement.x > 0)      currentRow = 48; // Right
        else if (movement.x < 0) currentRow = 96; // Left
        else if (movement.y > 0) currentRow = 0;  // Down
        else if (movement.y < 0) currentRow = 144; // Up

        isMoving = true;
    }
    else {
        // Random movement if player is not close
        switch (currentDirection) {
        case Right: movement.x += movementSpeed * movement_mult; break;
        case Left:  movement.x -= movementSpeed * movement_mult; break;
        case Down:  movement.y += movementSpeed * movement_mult; break;
        case Up:    movement.y -= movementSpeed * movement_mult; break;
        }
    }

    // Predict the next position for collision detection
    sf::FloatRect nextBounds = collisionBox.getGlobalBounds();
    nextBounds.left += movement.x;
    nextBounds.top += movement.y;

    bool collisionDetected = false;

    // Check for collisions with walls
    for (const auto& wall : wallSprites) {
        if (wall.getGlobalBounds().intersects(nextBounds)) {
            collisionDetected = true;
            break;
        }
    }

    // Check for collisions with player
    if (nextBounds.intersects(player.getCollisionBounds())) {
        std::cout << "Player hit!" << std::endl;
        player.playerHealth -= 1.f;
    }

    if (collisionDetected) {
        movement = sf::Vector2f(0.f, 0.f); // Stop movement if collision is detected
        currentDirection = getRandomDirection(); // Choose a new random direction
    }
    else {
        sprite.move(movement);
        updateCollisionBox();
    }

    // Update animation
    if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
        frameState = (frameState + 1) % 4; // Cycle through animation frames
        sprite.setTextureRect(sf::IntRect(48 * frameState, currentRow, 48, 48));
        animationClock.restart();
    }
}

void Zombie::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(collisionBox); // Optional: Draw collision box for debugging
}
