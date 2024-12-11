#include <SFML/Graphics.hpp>
#include "Maze.hpp"
#include "Player.hpp"
#include "Zombie.hpp"
#include <iostream>

using namespace std;
using namespace sf;

void runGame(sf::RenderWindow& window) {
    int level = 1;            // Start at level 1
    int mazeSize = 15;        // Initial maze size

    Maze maze(mazeSize, mazeSize, 48);
    Player player("textures/player/sprite_no_weapon.png", 0.1f, 100.f);
    player.setPosition(maze.getStartPosition().x, maze.getStartPosition().y);

    sf::View view(sf::FloatRect(0.f, 0.f, 1600.f, 1600.f));
    view.setCenter(player.getPosition());

    sf::Clock clock;

    // Spawn zombies
    const int zombieCount = 5; // Adjust the number of zombies per level
    const std::string zombieTexturePath = "textures/enemies/zombie.png";
    const float zombieMovementSpeed = 0.1f;
    const float zombieAnimationSpeed = 0.1f;

    // Generate zombies using the new Zombie::spawnZombies method
    std::vector<Zombie> zombies = Zombie::spawnZombies(
        zombieCount,
        maze.getBounds(),
        maze.getWallSprites(),
        zombieTexturePath,
        zombieMovementSpeed,
        zombieAnimationSpeed);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Exit to menu on Escape key
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
            view.setCenter(800.f, 800.f);
            window.setView(view);
            return;
        }

        float elapsedTime = clock.restart().asSeconds();
        player.handleInput(elapsedTime, maze.getWallSprites());
        maze.revealFog(player.getPosition(), 3);

        if (player.playerHealth == 0) {
            std::cout << "You died!" << std::endl;
            view.setCenter(800.f, 800.f);
            window.setView(view);
            return;
        }

        if (player.getCollisionBounds().intersects(maze.getEndMarker().getGlobalBounds())) {
            std::cout << "Level " << level << " Complete!" << std::endl;
            level++;
            mazeSize += 2;

            maze.reset(mazeSize, mazeSize, maze.getStartPosition());
            player.setPosition(maze.getStartPosition().x, maze.getStartPosition().y);

            // Spawn new zombies for the next level
            zombies = Zombie::spawnZombies(
                zombieCount + level,
                maze.getBounds(),
                maze.getWallSprites(),
                zombieTexturePath,
                zombieMovementSpeed,
                zombieAnimationSpeed);

            view.setCenter(player.getPosition());
        }

        if (level > 5) {
            std::cout << "You Win!" << std::endl;
            view.setCenter(800.f, 800.f);
            window.setView(view);
            return;
        }

        view.setCenter(player.getPosition());
        window.setView(view);

        window.clear();
        maze.draw(window);
        player.draw(window);

        for (auto& zombie : zombies) {
            zombie.update(player, player.getPosition(), maze.getWallSprites(), elapsedTime);
            zombie.draw(window, maze.getFogGrid(), maze.getCellSize());
        }


        window.display();
    }
}
