#ifndef MAZE_HPP
#define MAZE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Maze {
private:
    std::vector<std::vector<int>> grid; // 2D grid representation of the maze
   // std::vector<sf::Sprite> wallSprites; // Sprites for walls
    sf::Texture spriteSheet; // Texture for the maze (sprite sheet)
    sf::IntRect wallRect;    // Texture rectangle for walls
    sf::IntRect pathRect;    // Texture rectangle for paths
    std::vector<sf::Sprite> wallSprites; // Collidable wall sprites
    std::vector<sf::Sprite> pathSprites; // Non-collidable path sprites
    int cellSize;            // Size of each cell in pixels
    int width, height;       // Dimensions of the maze in cells

    sf::Vector2f endPosition; // Position of the end tile
    sf::RectangleShape endMarker; // End marker (tile)

    void carvePath(int x, int y); // Recursive backtracking for maze generation
    void placeEndTile(const sf::Vector2f& playerStart); // Place the end tile in a random corner

public:
    Maze(int width, int height, int cellSize);
    void generate(const sf::Vector2f& playerStart); // Regenerate the maze
    sf::Vector2f getStartPosition() const;          // Get the starting position of the maze
    //sf::Vector2f getEndPosition() const;            // Get the ending position of the maze
    const sf::RectangleShape& getEndMarker() const; // Get the end marker
    const std::vector<sf::Sprite>& getWallSprites() const; // Get wall sprites for collision
    void draw(sf::RenderWindow& window);            // Draw the maze
    void printToConsole(const sf::Vector2f& playerStart) const; // Print the maze to the console
    void reset(int newWidth, int newHeight, const sf::Vector2f& playerStart);

};

#endif
