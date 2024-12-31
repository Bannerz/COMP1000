#include "Zombie.hpp"
#include "Player.hpp"
#include <cmath>
#include <random>
#include <iostream>

using namespace std;

sf::Texture Zombie::zombieTexture; //define the static texture

Zombie::Zombie(float movementSpeed, float animationSpeed)
    : movementSpeed(movementSpeed), animationSpeed(animationSpeed), currentDirection(getRandomDirection()) {
    //ensure the texture is loaded
        if (!zombieTexture.loadFromFile("textures/enemies/zombie.png")) {
            std::cerr << "Error: Could not load zombie texture" << std::endl;
        }
    
    //set up zombie sprite
    sprite.setTexture(zombieTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, 48, 48)); //sprite sheet frames
    sprite.setScale(1.f, 1.f); //scale

    //collision box setup
    collisionBox.setSize(sf::Vector2f(14.f, 14.f)); //collisionbox size
    collisionBox.setFillColor(sf::Color(255, 0, 0, 100)); //red box for debugging
    collisionBox.setOrigin(-17.f, -30.f); //origin
}

//set position and collision box
void Zombie::setPosition(float x, float y) {
    sprite.setPosition(x, y);
    updateCollisionBox();
}
 
//update collision box to zombie position
void Zombie::updateCollisionBox() {
    collisionBox.setPosition(sprite.getPosition());
}

//choose a random direction for zombie movement
Zombie::Direction Zombie::getRandomDirection() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> randomDirection(0, 3);
    return static_cast<Direction>(randomDirection(rng));
}

//move zombie method
void Zombie::update(Player& player, const sf::Vector2f& playerPosition, const std::vector<sf::Sprite>& wallSprites, float elapsedTime) {
    sf::Vector2f movement(0.f, 0.f); // Initial movement vector
    float distanceToPlayer = std::hypot(sprite.getPosition().x - playerPosition.x, sprite.getPosition().y - playerPosition.y); //calc distance to player

    int movement_mult = 1; //speed multiplier for movement
    bool isMoving; //init is moving boolean

    if (distanceToPlayer < 200.f) { //detection radius
        sf::Vector2f targetDirection = playerPosition - sprite.getPosition(); //calculate direction to player
        targetDirection /= std::hypot(targetDirection.x, targetDirection.y); //normalize the vector

        sf::Vector2f potentialMovements[4] = { //movement options
            {movementSpeed * movement_mult, 0.f}, //right
            {-movementSpeed * movement_mult, 0.f}, //left
            {0.f, movementSpeed * movement_mult}, //down
            {0.f, -movementSpeed * movement_mult} //up
        };

        int priority[4] = { 0, 1, 2, 3 }; //indices of potentialMovements
        std::sort(priority, priority + 4, [&](int a, int b) {
            sf::Vector2f moveA = potentialMovements[a];
            sf::Vector2f moveB = potentialMovements[b];
            sf::Vector2f posA = sprite.getPosition() + moveA;
            sf::Vector2f posB = sprite.getPosition() + moveB;
            float distA = std::hypot(posA.x - playerPosition.x, posA.y - playerPosition.y);
            float distB = std::hypot(posB.x - playerPosition.x, posB.y - playerPosition.y);
            return distA < distB; //closer directions are prioritised
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

            //if collision is not detected set path found to true
            if (!collisionDetected) {
                movement += testMovement;
                pathFound = true;
                break;
            }
        }
        //if no direct path available, stop movement temporarily
        if (!pathFound) {
            movement = sf::Vector2f(0.f, 0.f); 
        }

        //determine animation row based on movement
        if (movement.x > 0) {
            currentRow = 48; //right
        }
        else if (movement.x < 0) {
            currentRow = 96; //left
        }
        else if (movement.y > 0) {
            currentRow = 0; //down
        }
        else if (movement.y < 0) {
            currentRow = 144; //up
        }

        isMoving = true; //set isMoving to true
    }
    else {
        //random movement if player is not close
        switch (currentDirection) {
        case Right: movement.x += movementSpeed * movement_mult; break;
        case Left:  movement.x -= movementSpeed * movement_mult; break;
        case Down:  movement.y += movementSpeed * movement_mult; break;
        case Up:    movement.y -= movementSpeed * movement_mult; break;
        }
    }

    //predict the next position for collision detection
    sf::FloatRect nextBounds = collisionBox.getGlobalBounds();
    nextBounds.left += movement.x;
    nextBounds.top += movement.y;

    bool collisionDetected = false;

    //check for collisions with walls
    for (const auto& wall : wallSprites) {
        if (wall.getGlobalBounds().intersects(nextBounds)) {
            collisionDetected = true;
            break;
        }
    }

    //check for collisions with player
    if (nextBounds.intersects(player.getCollisionBounds())) {
        player.playerHealth -= 0.1f; //damage
    }

    if (collisionDetected) {
        movement = sf::Vector2f(0.f, 0.f); //stop movement if collision is detected
        currentDirection = getRandomDirection(); //choose a new random direction
    }
    else {
        sprite.move(movement);
        updateCollisionBox();
    }

    //update animation
    if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
        frameState = (frameState + 1) % 4; //cycle through animation frames
        sprite.setTextureRect(sf::IntRect(48 * frameState, currentRow, 48, 48));
        animationClock.restart();
    }
}

void Zombie::draw(sf::RenderWindow& window, const std::vector<std::vector<bool>>& fogGrid, int cellSize) {
    //calculate the zombie's grid position
    sf::Vector2f position = sprite.getPosition();
    int gridX = static_cast<int>(position.x / cellSize);
    int gridY = static_cast<int>(position.y / cellSize);

    //check bounds to prevent out-of-range access
    if (gridY >= 0 && gridY < static_cast<int>(fogGrid.size()) &&
        gridX >= 0 && gridX < static_cast<int>(fogGrid[gridY].size())) {
        //draw the zombie only if the fog is not present
        if (!fogGrid[gridY][gridX]) { //false means the tile is revealed
            sprite.setColor(sf::Color(255, 255, 255, 255)); //fully visible
            window.draw(sprite); //draw zombie sprite

            //set collision box visibility (same as zombie)
            collisionBox.setFillColor(sf::Color(255, 0, 0, 100)); //semi-transparent red
            window.draw(collisionBox);
        } else {
            //set collision box transparency (visible in fog for debugging)
            collisionBox.setFillColor(sf::Color(255, 0, 0, 50)); //dimmed red for fogged tiles
            window.draw(collisionBox); //draw collision
        }
    }
}

//spawn zombies function
std::vector<Zombie> Zombie::spawnZombies(int zombieCount, const sf::FloatRect& mapBounds, const std::vector<sf::Sprite>& wallSprites, const std::string& zombieTexturePath, float movementSpeed, float animationSpeed) {
    std::vector<Zombie> zombies; //create zombies vector
    //random setups
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> randomX(mapBounds.left, mapBounds.left + mapBounds.width);
    std::uniform_real_distribution<float> randomY(mapBounds.top, mapBounds.top + mapBounds.height);

    int attempts = 0;
    while (zombies.size() < zombieCount && attempts < zombieCount * 10) {
        attempts++;

        //generate a random position within the map bounds
        float x = randomX(rng);
        float y = randomY(rng);

        //create a temporary zombie for collision checking
        Zombie tempZombie(movementSpeed, animationSpeed);
        tempZombie.setPosition(x, y);

        //check for collisions with walls
        bool collisionDetected = false;
        for (const auto& wall : wallSprites) {
            if (tempZombie.getCollisionBounds().intersects(wall.getGlobalBounds())) {
                collisionDetected = true;
                break;
            }
        }

        //if no collision, add the zombie to the list
        if (!collisionDetected) {
            zombies.push_back(tempZombie);
        }
    }

    //if too many zombies spawn
    if (zombies.size() < zombieCount) {
        std::cerr << "Warning: Could only spawn " << zombies.size() << " zombies out of " << zombieCount << "." << std::endl;
    }

    return zombies;
}
