#include "Player.hpp"
#include <iostream> // For debugging
using namespace std;

Player::Player(const std::string& texturePath, float animationSpeed, float movementSpeed)
    : animationSpeed(animationSpeed), movementSpeed(movementSpeed*4), frameState(0), currentRow(0) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error loading player texture" << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(48, 0, 48, 48)); // Default frame

    // Scale the sprite (adjust if needed)
    sprite.setScale(1.f, 1.f); // Double the size of the sprite

    // Initialize collision box
    collisionBox.setSize(sf::Vector2f(24.f, 24.f)); // Collision box is half the sprite size
    collisionBox.setFillColor(sf::Color(255, 0, 0, 100)); // Semi-transparent red for debugging
    collisionBox.setOrigin(-13.f, -22.f);
}

void Player::setPosition(float x, float y) {
    sprite.setPosition(x, y);
    updateCollisionBox();
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

sf::FloatRect Player::getCollisionBounds() const {
    return collisionBox.getGlobalBounds();
}

void Player::updateCollisionBox() {
    collisionBox.setPosition(sprite.getPosition());
}

void Player::handleInput(float elapsedTime, const std::vector<sf::Sprite>& wallSprites) {
    sf::Vector2f movement(0.f, 0.f);
    bool isMoving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= movementSpeed * elapsedTime;
        currentRow = 144; // Up animation row
        isMoving = true;
        //std::cout << "Moving Up" << endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += movementSpeed * elapsedTime;
        currentRow = 0; // Down animation row
        isMoving = true;
        //std::cout << "Moving Down" << endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= movementSpeed * elapsedTime;
        currentRow = 96; // Left animation row
        isMoving = true;
        //std::cout << "Moving Left" << endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += movementSpeed * elapsedTime;
        currentRow = 48; // Right animation row
        isMoving = true;
        //std::cout << "Moving Right" << endl;
    }

    sf::FloatRect nextBounds = collisionBox.getGlobalBounds();
    nextBounds.left += movement.x;
    nextBounds.top += movement.y;

    for (const auto& wall : wallSprites) {
        if (wall.getGlobalBounds().intersects(nextBounds)) {
            movement = sf::Vector2f(0.f, 0.f); // Block movement
            break;
        }
    }

    sprite.move(movement);
    updateCollisionBox();

    if (isMoving && animationClock.getElapsedTime().asSeconds() > animationSpeed) {
        frameState = (frameState + 1) % 4; // Cycle frames
        sprite.setTextureRect(sf::IntRect(48 * frameState, currentRow, 48, 48));
        animationClock.restart();
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(collisionBox); // Debugging: draw collision box
}
