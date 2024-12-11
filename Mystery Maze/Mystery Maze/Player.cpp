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

    // sprite scale
    sprite.setScale(1.f, 1.f); 

    //initialise collision box
    collisionBox.setSize(sf::Vector2f(16.f, 24.f)); //collision box size
    collisionBox.setFillColor(sf::Color(255, 0, 0, 100)); //semi-transparent red for debugging
    collisionBox.setOrigin(-16.f, -22.f);

    //initialise player health bar
    playerHealth = 48; //48 is temp, width of sprite

    healthBar.setSize(sf::Vector2f(playerHealth, 6.f)); //set width to player health and height to 6
    healthBar.setFillColor(sf::Color(0, 255, 0)); //set colour
    healthBar.setOrigin(0.f, -5.f); //set position
    std::cout << "Player health: "  << playerHealth << std::endl; //print the amount of health

}

void Player::health(float playerHealth) {

}

//set player position
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

void Player::updateHealthBar() {
    healthBar.setPosition(sprite.getPosition());

}

void Player::reduceHealth() {
    //health bar
    //playerHealth -= 1.f;
    healthBar.setSize(sf::Vector2f(playerHealth, 6.f)); //update the size
    // change color based on health
    if (playerHealth > 30) {
        healthBar.setFillColor(sf::Color::Green);
    }
    else if (playerHealth > 10) {
        healthBar.setFillColor(sf::Color::Yellow);
    }
    else {
        healthBar.setFillColor(sf::Color::Red);
    }
}

void Player::handleInput(float elapsedTime, const std::vector<sf::Sprite>& wallSprites) {
    sf::Vector2f movement(0.f, 0.f);
    bool isMoving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= movementSpeed * elapsedTime;
        currentRow = 144; //up animation row
        isMoving = true;
        //std::cout << "Moving Up" << endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += movementSpeed * elapsedTime;
        currentRow = 0; //down animation row
        isMoving = true;
        //std::cout << "Moving Down" << endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= movementSpeed * elapsedTime;
        currentRow = 96; //left animation row
        isMoving = true;
        //std::cout << "Moving Left" << endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += movementSpeed * elapsedTime;
        currentRow = 48; //right animation row
        isMoving = true;
        //std::cout << "Moving Right" << endl;
    }

    //wall collision
    sf::FloatRect nextBounds = collisionBox.getGlobalBounds();
    nextBounds.left += movement.x;
    nextBounds.top += movement.y;

    for (const auto& wall : wallSprites) {
        if (wall.getGlobalBounds().intersects(nextBounds)) {
            movement = sf::Vector2f(0.f, 0.f); //block movement
         
            break;
        }
    }

    sprite.move(movement);
    updateCollisionBox();
    reduceHealth();
    updateHealthBar();

    if (isMoving && animationClock.getElapsedTime().asSeconds() > animationSpeed) {
        frameState = (frameState + 1) % 4; // cycle frames
        sprite.setTextureRect(sf::IntRect(48 * frameState, currentRow, 48, 48));
        animationClock.restart();
    }
}


//draw player components 
void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite); //draw player sprite
    window.draw(collisionBox); //draw collision box for debugging
    window.draw(healthBar); //draw the health bar
}


