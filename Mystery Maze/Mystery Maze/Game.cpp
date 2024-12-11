#include <SFML/Graphics.hpp>
#include "Maze.hpp"
#include "Player.hpp"
#include "Zombie.hpp"
#include <iostream>

using namespace std;
using namespace sf;

void runGame(sf::RenderWindow& window) {
    int level = 1; //start at level 1
    int mazeSize = 15; //initial maze size

    Maze maze(mazeSize, mazeSize, 48); //last number is cell size
    Player player("textures/player/sprite_no_weapon.png", 0.1f, 100.f); //init player
    player.setPosition(maze.getStartPosition().x, maze.getStartPosition().y); //place player at start of maze

    sf::View view(sf::FloatRect(0.f, 0.f, 1600.f, 1600.f)); //create camera view
    view.setCenter(player.getPosition()); //centre the view on the player

    sf::Clock clock;

    //spawn zombies
    const int zombieCount = 5; //number of zombies per level (changeable on new level gen)
    const std::string zombieTexturePath = "textures/enemies/zombie.png"; //zombie texture path
    const float zombieMovementSpeed = 0.1f; //movement speed for zombie
    const float zombieAnimationSpeed = 0.1f; //anim speed for zombie

    //generate zombies using spawnZombies method
    std::vector<Zombie> zombies = Zombie::spawnZombies(zombieCount, maze.getBounds(), maze.getWallSprites(), zombieTexturePath, zombieMovementSpeed, zombieAnimationSpeed);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        //exit to menu on Escape key
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
            view.setCenter(800.f, 800.f); //move the view back to original position so the menu doesn't move
            window.setView(view); //set the view
            return; //actually return to previous menu
        }

        float elapsedTime = clock.restart().asSeconds(); //measure elapsed time in seconds
        player.handleInput(elapsedTime, maze.getWallSprites());
        maze.revealFog(player.getPosition(), 3); //call reveal fog and reveal the fog at players position in 3 tile radius

        //lose condition
        if (player.playerHealth <= 0) { //if the player loses all health, exit game and print you died. reset the view so menu doesnt move
            std::cout << "You died!" << std::endl;
            view.setCenter(800.f, 800.f);
            window.setView(view);
            return;
        }

        //level win condition
        if (player.getCollisionBounds().intersects(maze.getEndMarker().getGlobalBounds())) { //if the player reaches the end tile
            std::cout << "Level " << level << " Complete!" << std::endl; //print the level complete
            level++; //increase level
            mazeSize += 2; //increase maze size

            maze.reset(mazeSize, mazeSize, maze.getStartPosition()); //reset the maze
            player.setPosition(maze.getStartPosition().x, maze.getStartPosition().y); //place player at new maze

            //spawn new zombies for the next level
            zombies = Zombie::spawnZombies(zombieCount + level, maze.getBounds(), maze.getWallSprites(), zombieTexturePath, zombieMovementSpeed, zombieAnimationSpeed);

            //set view to player
            view.setCenter(player.getPosition());
        }

        //overall win condition
        if (level > 5) { //if player beats level 5
            std::cout << "You Win!" << std::endl; //print you win
            view.setCenter(800.f, 800.f); //reset view so menu doesn't move
            window.setView(view); //set the view
            return; //return to menu
        }

        view.setCenter(player.getPosition()); //reset view to player
        window.setView(view); //set view

        window.clear(); //clear the window
        maze.draw(window); //draw the maze
        player.draw(window); //draw the player

        //spawn and draw zombies
        for (auto& zombie : zombies) {
            zombie.update(player, player.getPosition(), maze.getWallSprites(), elapsedTime);
            zombie.draw(window, maze.getFogGrid(), maze.getCellSize());
        }

        //display the windows
        window.display();
    }
}
