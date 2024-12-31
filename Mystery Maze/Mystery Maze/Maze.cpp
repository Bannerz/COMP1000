#include "Maze.hpp"
#include "Zombie.hpp"
#include <random>
#include <algorithm>
#include <iostream>

//maze Constructor
Maze::Maze(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize) {
    if (!spriteSheet.loadFromFile("textures/environment/maze_sprites.png")) {
        std::cerr << "Error loading sprite sheet" << std::endl;
    }

    wallRect = sf::IntRect(0, 0, 32, 32);
    pathRect = sf::IntRect(32, 0, 32, 32);

    generate(getStartPosition());
}

//draw maze method
void Maze::draw(sf::RenderWindow& window) {
    for (const auto& path : pathSprites) {
        window.draw(path);
    }
    for (const auto& wall : wallSprites) {
        window.draw(wall);
    }

    //draw fog
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (fogGrid[y][x]) {


                sf::RectangleShape fogTile;
                fogTile.setSize(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize))); //set size to same as maze tile size
                fogTile.setPosition(static_cast<float>(x * cellSize), static_cast<float>(y * cellSize)); //place over whole maze
                fogTile.setFillColor(sf::Color::Black); //make fog blacl
                window.draw(fogTile); //draw
            }
        }
    }

    window.draw(endMarker); //draw the end marker
}




//get wall sprites
const std::vector<sf::Sprite>& Maze::getWallSprites() const {
    return wallSprites;
}

//get start position
sf::Vector2f Maze::getStartPosition() const {
    return sf::Vector2f(1.f * cellSize, 1.f * cellSize);
}

//get end marker
const sf::RectangleShape& Maze::getEndMarker() const {
    return endMarker;
}

const std::vector<std::vector<bool>>& Maze::getFogGrid() const {
    return fogGrid;
}


//place the end tile
void Maze::placeEndTile(const sf::Vector2f& playerStart) {
    std::vector<sf::Vector2f> corners = {
        sf::Vector2f((width - 2) * cellSize, 1.f * cellSize), //top right corner
        sf::Vector2f(1.f * cellSize, (height - 2) * cellSize), //bottom left corner
        sf::Vector2f((width - 2) * cellSize, (height - 2) * cellSize) //bottom right corner
    };

    corners.erase(std::remove(corners.begin(), corners.end(), playerStart), corners.end());

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(corners.size() - 1));
    endPosition = corners[dist(rng)];

    endMarker.setSize(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));
    endMarker.setPosition(endPosition);
    endMarker.setFillColor(sf::Color::Red); //make end tile red for debugging 9will change to texture)
}

//recursive backtracking carving method
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


//print the maze to console (for debugging)
void Maze::printToConsole(const sf::Vector2f& playerStart) const {
    std::cout << "\nMaze Layout:\n";
    sf::Vector2i startCell(static_cast<int>(playerStart.x / cellSize), static_cast<int>(playerStart.y / cellSize));
    sf::Vector2i endCell(static_cast<int>(endPosition.x / cellSize), static_cast<int>(endPosition.y / cellSize));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (sf::Vector2i(x, y) == startCell) {
                std::cout << "S "; //starting position
            }
            else if (sf::Vector2i(x, y) == endCell) {
                std::cout << "E "; //end position
            }
            else if (grid[y][x] == 0) {
                std::cout << "# "; //wall
            }
            else {
                std::cout << ". "; //path
            }
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}


//generate the maze
void Maze::generate(const sf::Vector2f& playerStart) {
    grid.resize(height, std::vector<int>(width, 0)); //initialize the grid with walls
    //std::cout << "Resizing fogGrid to " << height << "x" << width << std::endl; //debugging
    //resize fogGrid with the correct dimensions
    fogGrid.resize(height, std::vector<bool>(width, true));
    //debug if fogGrid does not match widrh
   /*for (int y = 0; y < fogGrid.size(); ++y) {
        for (int x = 0; x < fogGrid[y].size(); x++) {
            std::cout << fogGrid[y][x] << " ";
        }
        std::cout << std::endl;
    }*/

    wallSprites.clear(); //clear existing wall sprites


    carvePath(1, 1);        //start carving paths from (1, 1)
    placeEndTile(playerStart); //slace the end tile in one of the far corners
    printToConsole(playerStart); // Print the maze to the console


    //apply the textures to the walls and paths of the maze
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            sf::Sprite sprite;
            sprite.setTexture(spriteSheet);
            sprite.setPosition(static_cast<float>(x * cellSize), static_cast<float>(y * cellSize));
            sprite.setScale(static_cast<float>(cellSize) / wallRect.width,
                static_cast<float>(cellSize) / wallRect.height);

            if (grid[y][x] == 0) { //wall
                sprite.setTextureRect(wallRect);
                wallSprites.push_back(sprite); //collidable
            }
            else { //path
                sprite.setTextureRect(pathRect);
                pathSprites.push_back(sprite); //non collidable
            }
        }
    }


}



//reset the maze for when player reaches end tile
void Maze::reset(int newWidth, int newHeight, const sf::Vector2f& playerStart) {
    width = newWidth;
    height = newHeight;
    grid.clear();         //reset the grid
    wallSprites.clear();  //reset the wall sprites
    pathSprites.clear();  //reset the path sprites
    fogGrid.clear();      //clear the fog grid
    fogGrid.resize(height, std::vector<bool>(width, true)); //reinitialise fog
    generate(playerStart);
}

//mehtod for revealing the maze as the player moves through the maze
void Maze::revealFog(const sf::Vector2f& playerPosition, int revealRadius) {
    int playerX = static_cast<int>(playerPosition.x / cellSize);
    int playerY = static_cast<int>(playerPosition.y / cellSize);

    for (int y = playerY - revealRadius; y <= playerY + revealRadius; ++y) {
        for (int x = playerX - revealRadius; x <= playerX + revealRadius; ++x) {
            if (y < 0 || y >= height || x < 0 || x >= width) {
                continue; //skip out of bounds
            }
            if (std::hypot(x - playerX, y - playerY) <= revealRadius && fogGrid[y][x]) {
                fogGrid[y][x] = false; //reveal this tile
                fogUpdated = true;    //mark that fog has changed
            }
        }
    }
}

sf::FloatRect Maze::getBounds() const {
    float widthInPixels = static_cast<float>(width * cellSize);  //calculate maze width in pixels
    float heightInPixels = static_cast<float>(height * cellSize); //calculate maze height in pixels
    return sf::FloatRect(0.f, 0.f, widthInPixels, heightInPixels); //top left at 0, 0
}

std::vector<int> Maze::flatten() const {
    std::vector<int> flat;
    for (const auto& row : grid) { // Assuming mazeGrid is your 2D grid
        flat.insert(flat.end(), row.begin(), row.end());
    }
    return flat;
}

void Maze::generateFromData(int size, const std::vector<int>& data) {
    grid.resize(size, std::vector<int>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            grid[i][j] = data[i * size + j];
        }
    }
}

