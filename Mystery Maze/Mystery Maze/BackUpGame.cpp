/*#include <SFML/Graphics.hpp>
#include "Maze.hpp"
#include "Player.hpp"
#include "Zombie.hpp"
#include <iostream>
using namespace std;
using namespace sf;

std::vector<Zombie> zombies;


int game() {
    sf::RenderWindow window(sf::VideoMode(1600, 1600), "Mystery Maze");

    //load window icon because its pretty
    sf::Image icon;
    icon.loadFromFile("textures/ui/icon.png"); //file path
    window.setIcon(16, 16, icon.getPixelsPtr()); //set icon and pointers

    window.setFramerateLimit(60);

    int level = 1; // Start at level 1
    int mazeSize = 15; // Initial maze size


    Maze maze(mazeSize, mazeSize, 48);
    Player player("textures/player/sprite_no_weapon.png", 0.1f, 100.f); //second number is player movement speed

    player.setPosition(maze.getStartPosition().x, maze.getStartPosition().y);

    Zombie zombie("textures/enemies/zombie.png", 0.1f, 100.f);

    zombie.setPosition(40.f, 70.f); // Set position of the Zombie (loop for random gen?)




    sf::View view(sf::FloatRect(0.f, 0.f, 800.f, 800.f));
    view.setCenter(player.getPosition());

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }



        float elapsedTime = clock.restart().asSeconds();
        player.handleInput(elapsedTime, maze.getWallSprites());

        maze.revealFog(player.getPosition(), 3); // Reveal a radius of 3 tiles

        if (player.playerHealth == 0) {
            window.close();
            std::cout << "You died!" << std::endl;
        }

        // Check if the player reaches the end tile
        if (player.getCollisionBounds().intersects(maze.getEndMarker().getGlobalBounds())) {
            std::cout << "Level " << level << " Complete!" << std::endl;

            // Increase difficulty
            level++;
            mazeSize += 2; // Increase the maze size


            maze.reset(mazeSize, mazeSize, maze.getStartPosition());
            maze.generate(player.getPosition());
            player.setPosition(maze.getStartPosition().x, maze.getStartPosition().y);

            view.setCenter(player.getPosition()); // Reset the view
        }
        if (level > 5) { //limit levels
            std::cout << "You Win!" << endl;
            window.close();
        }

        view.setCenter(player.getPosition());
        window.setView(view);

        window.clear();
        maze.draw(window);
        player.draw(window);
        /*for (auto& zombie : zombies) {
            zombie.update(player.getPosition(), maze.getWallSprites(), elapsedTime); // Update movement
            zombie.draw(window); // Draw zombie
        }*//*
        zombie.update(player, player.getPosition(), maze.getWallSprites(), elapsedTime);
        zombie.draw(window);
        window.display();
    }

    return 0;
}
*/