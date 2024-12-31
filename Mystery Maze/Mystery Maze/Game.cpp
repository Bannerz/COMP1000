#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "Maze.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Health.hpp"
#include "Zombie.hpp"
#include "Potions.hpp"
#include "Winner.hpp"
#include "Loser.hpp"
#include "Timer.hpp"
#include "Score.hpp"
#include "Puzzle.hpp"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void runGame(sf::RenderWindow& window) {
    int level = 1; //start at level 1
    int mazeSize = 15; //initial maze size

    Winner winner; //initialise winner
    Loser loser; //initialise loser
    Timer timer(30); //initialise timer and set level time
    timer.update(window);
    Score score(0);
    score.update(window);

    Maze maze(mazeSize, mazeSize, 48); //last number is cell size
    Player player("textures/player/sprite_no_weapon.png", 0.1f, 100.f); //init player
    Health health("textures/items/heart.png");
    player.setPosition(maze.getStartPosition().x, maze.getStartPosition().y); //place player at start of maze

    int playerLives = 3; //set players lives

    health.setLives(playerLives); //set amount of player lives to health class

    sf::View view(sf::FloatRect(0.f, 0.f, 1600.f, 1600.f)); //create camera view
    view.setCenter(player.getPosition()); //centre the view on the player

    sf::Clock clock; //aniimation clock

    //load game music
    sf::Music gameMusic;
    if (!gameMusic.openFromFile("audio/baroque-summer-loop.mp3")) {
        std::cerr << "No music file found" << std::endl;
    }

    gameMusic.play(); //play music
    //spawn zombies
    const int zombieCount = 5; //number of zombies per level (changeable on new level gen)
    const std::string zombieTexturePath = "textures/enemies/zombie.png"; //zombie texture path
    const float zombieMovementSpeed = 0.1f; //movement speed for zombie
    const float zombieAnimationSpeed = 0.1f; //anim speed for zombie

    //spawn potions
    const int potionCount = 5; //number of zombies per level (changeable on new level gen)
    const std::string healthPotPath = "textures/items/healthPot.png"; //zombie texture path

    //generate zombies using spawnZombies method
    std::vector<Zombie> zombies = Zombie::spawnZombies(zombieCount, maze.getBounds(), maze.getWallSprites(), zombieTexturePath, zombieMovementSpeed, zombieAnimationSpeed);

    //generate potions using spawnPotions method
    std::vector<Potions> potion = Potions::spawnPotions(potionCount, maze.getBounds(), maze.getWallSprites(), healthPotPath);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            //exit to menu on Escape key
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
                view.setCenter(800.f, 800.f); //move the view back to original position so the menu doesn't move
                window.setView(view); //set the view
                return; //actually return to previous menu
            }

            if (event.type == sf::Event::KeyPressed) {
                //save with key
                if (event.key.code == sf::Keyboard::P) {
                    saveState state;
                    state.level = level;
                    state.mazeSize = mazeSize;
                    state.playerLives = playerLives;
                    state.playerScore = score.getPlayerScore();
                    state.playerX = player.getPosition().x;
                    state.playerY = player.getPosition().y;
                    state.timerRemaining = timer.getRemainingTime();
                    state.mazeData = maze.flatten(); //flatten the maze into a 1D vector
                    std::cout << "Saving state:" << std::endl;
                    std::cout << "Level: " << state.level << std::endl;
                    std::cout << "Maze Size: " << state.mazeSize << std::endl;
                    std::cout << "Player Lives: " << state.playerLives << std::endl;
                    std::cout << "Player Score: " << state.playerScore << std::endl;
                    std::cout << "Player Position: (" << state.playerX << ", " << state.playerY << ")" << std::endl;
                    std::cout << "Timer Remaining: " << state.timerRemaining << std::endl;
                    std::cout << "Maze Data Size: " << state.mazeData.size() << std::endl;
                    saveGameState(state, "saves/savegame.dat");
                    std::cout << "Game saved!" << std::endl;
                }

                //load with key
                if (event.key.code == sf::Keyboard::O) {
                    saveState state;
                    if (loadGameState(state, "saves/savegame.dat")) {
                        level = state.level;
                        mazeSize = state.mazeSize;
                        playerLives = state.playerLives;
                        score.setPlayerScore(state.playerScore);
                        player.setPosition(state.playerX, state.playerY);
                        if (state.timerRemaining > 0) {
                            timer.setRemainingTime(state.timerRemaining);
                        }
                        else {
                            std::cerr << "Warning: Loaded timerRemaining is invalid!" << std::endl;
                        }

                        maze.generateFromData(state.mazeSize, state.mazeData);
                        std::cout << "Game loaded!" << std::endl;
                    }
                }
            }
        }

       

        float elapsedTime = clock.restart().asSeconds(); //measure elapsed time in seconds
        player.handleInput(elapsedTime, maze.getWallSprites());
        maze.revealFog(player.getPosition(), 3); //call reveal fog and reveal the fog at players position in 3 tile radius
        
        if (timer.remainingTime <= 0) {
            std::cout << "You lost the game!" << std::endl;
            view.setCenter(800.f, 800.f); //reset view so menu doesn't move
            window.setView(view); //set the view
            int finalScore = score.getPlayerScore();
            loser.runOOT(window, finalScore); //call the function from Credits.cpp
            return; //return to menu
        }

        //lose condition
        //if player dies, remove life, if life = 0 end game
        if (player.playerHealth <= 0) { //if the player loses all health, exit game and print you died. reset the view so menu doesnt move
            std::cout << "You lost a life!" << std::endl; //debug losing life
            playerLives += -1; //remove life
            health.setLives(playerLives); //change hearts sprites vector
            player.playerHealth = 48; //reset player health
            std::cout << "Lives remaining:" << playerLives << std::endl; //debug losing life
        }
        //if player runs out of lives, end the game
        if (playerLives == 0) {
            std::cout << "You lost the game!" << std::endl;
            view.setCenter(800.f, 800.f); //reset view so menu doesn't move
            window.setView(view); //set the view
            int finalScore = score.getPlayerScore();
            loser.runLoseScreen(window, finalScore); //call the function from Credits.cpp
            return; //return to menu
        } 

        //check for overall win condition before everything else
        if (level > 5) {
            std::cout << "You Win!" << std::endl;
            int finalScore = score.getPlayerScore();
            view.setCenter(800.f, 800.f); //reset view
            window.setView(view); //apply reset view
            winner.runWinScreen(window, finalScore); //show win screen
            return; //return to menu
        }

        //level win condition
        if (player.getCollisionBounds().intersects(maze.getEndMarker().getGlobalBounds())) {
            Puzzle puzzle;
            if (puzzle.run(window)) {
                std::cout << "Puzzle solved successfully!" << std::endl;
                level++; //increase level
                mazeSize += 2; //increase maze size

                //progress to the next level
                std::cout << "Level " << level << " Complete!" << std::endl;
                int timeScore = static_cast<int>(timer.getRemainingTime() * 10);
                int puzzleScore = 100;
                score.scoreUp(timeScore + puzzleScore);
                timer.reset();
                maze.reset(mazeSize, mazeSize, maze.getStartPosition());
                player.setPosition(maze.getStartPosition().x, maze.getStartPosition().y);

                //spawn new zombies and potions for the next level
                zombies = Zombie::spawnZombies(zombieCount + level, maze.getBounds(), maze.getWallSprites(), zombieTexturePath, zombieMovementSpeed, zombieAnimationSpeed);
                potion = Potions::spawnPotions(5, maze.getBounds(), maze.getWallSprites(), "textures/items/healthPot.png");

                view.setCenter(player.getPosition()); //reset view to player
            }
            else {
                //player exited or failed
                std::cout << "Puzzle not solved. Exiting to menu." << std::endl;
                return;
            }
        }

        health.updatePosition(window); //update position of the hearts
        timer.update(window); //update position of timer
        score.update(window); //update position of score
        view.setCenter(player.getPosition()); //reset view to player
        window.setView(view); //set view
        window.clear(); //clear the window
        maze.draw(window); //draw the maze
        player.draw(window); //draw the player
        health.draw(window); //draw hearts

        //spawn and draw zombies
        for (auto& zombie : zombies) {
            zombie.update(player, player.getPosition(), maze.getWallSprites(), elapsedTime);
            zombie.draw(window, maze.getFogGrid(), maze.getCellSize());
        }

        //spawn and draw potions
        for (auto it = potion.begin(); it != potion.end(); ) {
            it->update(player); //update the potion

            if (it->shouldDespawn()) { //check if the potion is inactive
                it = potion.erase(it); //erase the potion and update the iterator
            }
            else {
                it->draw(window, maze.getFogGrid(), maze.getCellSize()); //draw the active potion
                ++it; //increment the iterator
            }
        }
        timer.draw(window); //draw timer
        score.draw(window); //draw score
        //display the windows
        window.display();
    }
}

void saveGameState(const saveState& state, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "failed to create or open save file" << std::endl;
        return;
    }

    //write the state header
    file.write(reinterpret_cast<const char*>(&state.level), sizeof(state.level));
    file.write(reinterpret_cast<const char*>(&state.mazeSize), sizeof(state.mazeSize));
    file.write(reinterpret_cast<const char*>(&state.playerLives), sizeof(state.playerLives));
    file.write(reinterpret_cast<const char*>(&state.playerScore), sizeof(state.playerScore));
    file.write(reinterpret_cast<const char*>(&state.playerX), sizeof(state.playerX));
    file.write(reinterpret_cast<const char*>(&state.playerY), sizeof(state.playerY));
    file.write(reinterpret_cast<const char*>(&state.timerRemaining), sizeof(state.timerRemaining));

    //validate and write maze data size
    size_t mazeDataSize = state.mazeData.size();
    file.write(reinterpret_cast<const char*>(&mazeDataSize), sizeof(mazeDataSize));

    //write the maze data
    file.write(reinterpret_cast<const char*>(state.mazeData.data()), mazeDataSize * sizeof(int));
    file.close();//close file

    std::cout << "Game saved" << std::endl;
}

bool loadGameState(saveState& state, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open save file" << std::endl;
        return false;
    }

    //read the state header
    file.read(reinterpret_cast<char*>(&state.level), sizeof(state.level));
    file.read(reinterpret_cast<char*>(&state.mazeSize), sizeof(state.mazeSize));
    file.read(reinterpret_cast<char*>(&state.playerLives), sizeof(state.playerLives));
    file.read(reinterpret_cast<char*>(&state.playerScore), sizeof(state.playerScore));
    file.read(reinterpret_cast<char*>(&state.playerX), sizeof(state.playerX));
    file.read(reinterpret_cast<char*>(&state.playerY), sizeof(state.playerY));
    file.read(reinterpret_cast<char*>(&state.timerRemaining), sizeof(state.timerRemaining));

    //read and validate maze data size
    size_t mazeDataSize;
    file.read(reinterpret_cast<char*>(&mazeDataSize), sizeof(mazeDataSize));

    //read the maze data
    state.mazeData.resize(mazeDataSize);
    file.read(reinterpret_cast<char*>(state.mazeData.data()), mazeDataSize * sizeof(int));

    file.close();//close file

    return true;
}


