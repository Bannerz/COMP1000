#ifndef MAZE_HPP
#define MAZE_HPP

#include <SFML/Graphics.hpp> //include graphics library
#include <vector> //include vector library

class Maze {
private:
    std::vector<std::vector<int>> grid; //2D grid representation of the maze
    sf::Texture spriteSheet; //maze spritesheet
    sf::IntRect wallRect; //texture rectangle for walls
    sf::IntRect pathRect; //texture rectangle for paths
    std::vector<sf::Sprite> wallSprites; //collidable wall sprites
    std::vector<sf::Sprite> pathSprites; //non collidable path sprites
    int cellSize; //size of each cell in pixels
    int width, height; //dimensions of the maze in cells

    sf::Vector2f endPosition; //position of the end tile
    sf::RectangleShape endMarker; //end tile

    std::vector<std::vector<bool>> fogGrid; //fog state for each tile
    bool fogUpdated = false; //track if fog visibility has changed


    void carvePath(int x, int y); //recursive backtracking for maze generation
    void placeEndTile(const sf::Vector2f& playerStart); //place the end tile in a random corner (1/3)

public:
    Maze(int width, int height, int cellSize); //set maze dimensions
    void generate(const sf::Vector2f& playerStart); //generate the maze
    sf::Vector2f getStartPosition() const; //get the starting position of the maze
    const sf::RectangleShape& getEndMarker() const; //get the end marker
    const std::vector<sf::Sprite>& getWallSprites() const; //get wall sprites 
    void draw(sf::RenderWindow& window); //draw maze method
    void printToConsole(const sf::Vector2f& playerStart) const; //print the maze to the console for debug
    void reset(int newWidth, int newHeight, const sf::Vector2f& playerStart); //reset mze
    void revealFog(const sf::Vector2f& playerPosition, int revealRadius); //reveal fog
    const std::vector<std::vector<bool>>& getFogGrid() const; //get the fog grid
    int getGridHeight() const { return height; } //get the fog grid height
    int getGridWidth() const { return width; } //get the fog grid width
    const std::vector<std::vector<int>>& getGrid() const { return grid; } //get the grid
    int getCellSize() const { return cellSize; } //get the cell size
    sf::FloatRect getBounds() const; //get bounds

};

#endif
