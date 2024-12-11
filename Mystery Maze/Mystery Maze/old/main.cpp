#include <SFML/Graphics.hpp>
#include "Maze.hpp"
#include "Player.hpp"
#include <iostream>
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Mystery Maze");
    window.setFramerateLimit(60);

    int level = 1; // Start at level 1
    int mazeSize = 15; // Initial maze size

   
    Maze maze(mazeSize, mazeSize, 48); 
    Player player("textures/player/sprite_no_weapon.png", 0.1f, 100.f);

    player.setPosition(maze.getStartPosition().x, maze.getStartPosition().y);

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

        // Check if the player reaches the end tile
        if (player.getCollisionBounds().intersects(maze.getEndMarker().getGlobalBounds())) {
            std::cout << "Level " << level << " Complete!" << std::endl;

            // Increase difficulty
            level++;
            mazeSize += 2; // Increase the maze size
            maze.reset(mazeSize, mazeSize, maze.getStartPosition());
            player.setPosition(maze.getStartPosition().x, maze.getStartPosition().y);

            view.setCenter(player.getPosition()); // Reset the view
        }
        if (level > 5) {
            std::cout << "You Win!" << endl;
            window.close();
        }

        view.setCenter(player.getPosition());
        window.setView(view);

        window.clear();
        maze.draw(window);
        player.draw(window);
        window.display();
    }

    return 0;
}
