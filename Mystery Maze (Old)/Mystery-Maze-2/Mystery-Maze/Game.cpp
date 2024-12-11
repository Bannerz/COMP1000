#include <SFML/Graphics.hpp>
#include "Maze.hpp"
#include "Player.hpp"
#include "Zombie.hpp"
#include <iostream>
using namespace std;
using namespace sf;

std::vector<Zombie> zombies;

#include <random>

// Function to spawn zombies
std::vector<Zombie> spawnZombies(int zombieCount,
    const sf::FloatRect& mapBounds,
    const std::vector<sf::Sprite>& wallSprites,
    const std::string& texturePath,
    float movementSpeed,
    float animationSpeed) {
    std::vector<Zombie> zombies;
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> randomX(mapBounds.left, mapBounds.left + mapBounds.width);
    std::uniform_real_distribution<float> randomY(mapBounds.top, mapBounds.top + mapBounds.height);

    int attempts = 0;
    while (zombies.size() < zombieCount && attempts < zombieCount * 10) {
        attempts++;

        // Generate a random position within the map bounds
        float x = randomX(rng);
        float y = randomY(rng);

        // Create a temporary zombie for collision checking
        Zombie tempZombie(texturePath, movementSpeed, animationSpeed);
        tempZombie.setPosition(x, y);

        // Check for collisions with walls
        bool collisionDetected = false;
        for (const auto& wall : wallSprites) {
            if (tempZombie.getCollisionBounds().intersects(wall.getGlobalBounds())) {
                collisionDetected = true;
                break;
            }
        }

        // If no collision, add the zombie to the list
        if (!collisionDetected) {
            zombies.push_back(tempZombie);
        }
    }

    if (zombies.size() < zombieCount) {
        std::cerr << "Warning: Could only spawn " << zombies.size() << " zombies out of " << zombieCount << "." << std::endl;
    }

    return zombies;
}


void runGame(sf::RenderWindow& window) {
    int level = 1;            // Start at level 1
    int mazeSize = 15;        // Initial maze size

    Maze maze(mazeSize, mazeSize, 48);
    Player player("textures/player/sprite_no_weapon.png", 0.1f, 100.f); // Player setup

    player.setPosition(maze.getStartPosition().x, maze.getStartPosition().y);

    sf::View view(sf::FloatRect(0.f, 0.f, 1600.f, 1600.f));
    view.setCenter(player.getPosition());

    sf::Clock clock;

    // Spawn zombies
    const int zombieCount = 5; // Adjust the number of zombies per level
    const std::string zombieTexturePath = "textures/enemies/zombie.png";
    const float zombieMovementSpeed = 0.1f;
    const float zombieAnimationSpeed = 0.1f;

    // Generate zombies
    zombies = spawnZombies(zombieCount, maze.getBounds(), maze.getWallSprites(), zombieTexturePath, zombieMovementSpeed, zombieAnimationSpeed);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Exit to menu on Escape key
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
            view.setCenter(800.f, 800.f); // Adjust view center
            window.setView(view);
            return; // Exit game to menu
        }

        float elapsedTime = clock.restart().asSeconds();
        player.handleInput(elapsedTime, maze.getWallSprites());
        maze.revealFog(player.getPosition(), 3); // Reveal a radius of 3 tiles

        // Handle Player Death
        if (player.playerHealth == 0) {
            std::cout << "You died!" << std::endl;
            level = 1;          // Reset level
            mazeSize -= mazeSize * level;
            view.setCenter(800.f, 800.f); // Reset view
            window.setView(view);
            return;
        }

        // Check if player reaches the end tile
        if (player.getCollisionBounds().intersects(maze.getEndMarker().getGlobalBounds())) {
            std::cout << "Level " << level << " Complete!" << std::endl;

            // Increase difficulty
            level++;
            mazeSize += 2; // Increase maze size

            maze.reset(mazeSize, mazeSize, maze.getStartPosition());
            maze.generate(player.getPosition());
            player.setPosition(maze.getStartPosition().x, maze.getStartPosition().y);

            // Spawn new zombies for the next level
            zombies = spawnZombies(zombieCount + level, maze.getBounds(), maze.getWallSprites(), zombieTexturePath, zombieMovementSpeed, zombieAnimationSpeed);

            view.setCenter(player.getPosition()); // Reset the view
        }

        if (level > 5) { // Win condition
            std::cout << "You Win!" << std::endl;
            view.setCenter(800.f, 800.f);
            window.setView(view);
            return;
        }

        // Update View
        view.setCenter(player.getPosition());
        window.setView(view);

        // Game Rendering
        window.clear();
        maze.draw(window);
        player.draw(window);

        // Update and draw zombies
        for (auto& zombie : zombies) {
            zombie.update(player, player.getPosition(), maze.getWallSprites(), elapsedTime); // Update zombie movement
            zombie.draw(window); // Draw zombie
        }

        window.display();
    }
}
