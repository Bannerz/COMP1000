#include "Maze.hpp"
#include <random>
#include <algorithm>
#include <iostream> // For debugging

// Constructor
Maze::Maze(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize) {
    if (!spriteSheet.loadFromFile("textures/environment/maze_sprites.png")) {
        std::cerr << "Error loading sprite sheet" << std::endl;
    }

    wallRect = sf::IntRect(0, 0, 32, 32);
    pathRect = sf::IntRect(32, 0, 32, 32);

    generate(getStartPosition());
}

// Draw the maze
void Maze::draw(sf::RenderWindow& window) {
    for (const auto& path : pathSprites) {
        window.draw(path); // Draw non-collidable paths
    }
    for (const auto& wall : wallSprites) {
        window.draw(wall); // Draw collidable walls
    }
    window.draw(endMarker); // Draw the end marker
}



// Get wall sprites
const std::vector<sf::Sprite>& Maze::getWallSprites() const {
    return wallSprites;
}

// Get start position
sf::Vector2f Maze::getStartPosition() const {
    return sf::Vector2f(1.f * cellSize, 1.f * cellSize);
}

// Get end marker
const sf::RectangleShape& Maze::getEndMarker() const {
    return endMarker;
}

// Place end tile
void Maze::placeEndTile(const sf::Vector2f& playerStart) {
    std::vector<sf::Vector2f> corners = {
        sf::Vector2f((width - 2) * cellSize, 1.f * cellSize),                  // Top-right corner
        sf::Vector2f(1.f * cellSize, (height - 2) * cellSize),                 // Bottom-left corner
        sf::Vector2f((width - 2) * cellSize, (height - 2) * cellSize)          // Bottom-right corner
    };

    corners.erase(std::remove(corners.begin(), corners.end(), playerStart), corners.end());

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(corners.size() - 1));
    endPosition = corners[dist(rng)];

    endMarker.setSize(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));
    endMarker.setPosition(endPosition);
    endMarker.setFillColor(sf::Color::Red); // Red for the end tile
}

// Carve paths recursively
void Maze::carvePath(int x, int y) {
    grid[y][x] = 1;

    std::vector<std::pair<int, int>> directions = { {0, -2}, {0, 2}, {-2, 0}, {2, 0} };
    std::random_shuffle(directions.begin(), directions.end());

    for (auto& dir : directions) {
        int nx = x + dir.first;
        int ny = y + dir.second;

        if (ny > 0 && ny < height - 1 && nx > 0 && nx < width - 1 && grid[ny][nx] == 0) {
            grid[y + dir.second / 2][x + dir.first / 2] = 1;
            carvePath(nx, ny);
        }
    }
}

void Maze::generate(const sf::Vector2f& playerStart) {
    grid.resize(height, std::vector<int>(width, 0)); // Initialize the grid with walls
    wallSprites.clear();                            // Clear existing wall sprites


    carvePath(1, 1);        // Start carving paths from (1, 1)
    placeEndTile(playerStart); // Place the end tile in one of the far corners

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            sf::Sprite sprite;
            sprite.setTexture(spriteSheet);
            sprite.setPosition(static_cast<float>(x * cellSize), static_cast<float>(y * cellSize));
            sprite.setScale(static_cast<float>(cellSize) / wallRect.width,
                static_cast<float>(cellSize) / wallRect.height);

            if (grid[y][x] == 0) { // Wall
                sprite.setTextureRect(wallRect);
                wallSprites.push_back(sprite); // Collidable
            }
            else { // Path
                sprite.setTextureRect(pathRect);
                pathSprites.push_back(sprite); // Non-collidable
            }
        }
    }


    printToConsole(playerStart); // Print the maze to the console
}

void Maze::printToConsole(const sf::Vector2f& playerStart) const {
    std::cout << "\nMaze Layout:\n";
    sf::Vector2i startCell(static_cast<int>(playerStart.x / cellSize), static_cast<int>(playerStart.y / cellSize));
    sf::Vector2i endCell(static_cast<int>(endPosition.x / cellSize), static_cast<int>(endPosition.y / cellSize));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (sf::Vector2i(x, y) == startCell) {
                std::cout << "S "; // Starting position
            } else if (sf::Vector2i(x, y) == endCell) {
                std::cout << "E "; // End position
            } else if (grid[y][x] == 0) {
                std::cout << "# "; // Wall
            } else {
                std::cout << ". "; // Path
            }
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void Maze::reset(int newWidth, int newHeight, const sf::Vector2f& playerStart) {
    width = newWidth;
    height = newHeight;
    grid.clear();        // Reset the grid
    wallSprites.clear(); // Reset the wall sprites
    generate(playerStart);
}
