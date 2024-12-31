#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Function to handle game logic
void runGame(sf::RenderWindow& window);

// Struct to represent the game state
struct saveState {
    int level = 0;
    int mazeSize = 0;
    int playerLives = 0;
    int playerScore = 0;
    float playerX = 0.0f;
    float playerY = 0.0f;
    float timerRemaining = 0.0f;
    std::vector<int> mazeData;
};


// Save game state to a file
void saveGameState(const saveState& state, const std::string& filename);

// Load game state from a file
bool loadGameState(saveState& state, const std::string& filename);
