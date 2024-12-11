#include <SFML/Graphics.hpp>

enum Direction { Down, Left, Right, Up };

const int FRAME_WIDTH = 14;
const int FRAME_HEIGHT = 32;
const int FRAMES_PER_DIRECTION = 4;

// 2D array for each direction (Down, Left, Right, Up)
const sf::IntRect frameRects[4][FRAMES_PER_DIRECTION] = {
    // Down frames
    { {17, 14, FRAME_WIDTH, FRAME_HEIGHT}, {FRAME_WIDTH, 17, FRAME_WIDTH, FRAME_HEIGHT}, {2 * FRAME_WIDTH, 14, FRAME_WIDTH, FRAME_HEIGHT}, {3 * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT} },
    // Left frames
    { {0, FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT}, {FRAME_WIDTH, FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT}, {2 * FRAME_WIDTH, FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT}, {3 * FRAME_WIDTH, FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT} },
    // Right frames
    { {0, 2 * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT}, {FRAME_WIDTH, 2 * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT}, {2 * FRAME_WIDTH, 2 * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT}, {3 * FRAME_WIDTH, 2 * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT} },
    // Up frames
    { {0, 3 * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT}, {FRAME_WIDTH, 3 * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT}, {2 * FRAME_WIDTH, 3 * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT}, {3 * FRAME_WIDTH, 3 * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT} }
};


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Animated Sprite");

    sf::Texture texture;
    if (!texture.loadFromFile("C:/Users/Alex/source/repos/Mystery-Maze/sprite_no_weapon.png")) return -1;

    sf::Sprite sprite(texture);
    sprite.setScale(3.f, 3.f); // Scale for visibility
    sprite.setPosition(60, 60);

    Direction direction = Down;
    int frame = 0;
    float animationSpeed = 0.1f;
    sf::Clock clock, animationClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Movement and direction handling
        sf::Vector2f movement(0.f, 0.f);
        bool isMoving = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            direction = Up;
            movement.y -= 100 * clock.restart().asSeconds();
            isMoving = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            direction = Down;
            movement.y += 100 * clock.restart().asSeconds();
            isMoving = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            direction = Left;
            movement.x -= 100 * clock.restart().asSeconds();
            isMoving = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            direction = Right;
            movement.x += 100 * clock.restart().asSeconds();
            isMoving = true;
        }

        // Update animation frame if moving
        if (isMoving && animationClock.getElapsedTime().asSeconds() > animationSpeed) {
            frame = (frame + 1) % FRAMES_PER_DIRECTION;
            animationClock.restart();
        }
        else if (!isMoving) {
            frame = 0; // Reset frame if not moving
        }

        // Apply frame and movement
        sprite.setTextureRect(frameRects[direction][frame]);
        sprite.move(movement);

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
