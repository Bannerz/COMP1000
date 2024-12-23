#include "Health.hpp"
#include <iostream>
using namespace std;

Health::Health(const std::string& healthTexPath) {
    if (!healthTexture.loadFromFile(healthTexPath)) {
        std::cerr << "Error loading heart texture" << std::endl;
    }
    else {
        std::cerr << "Heart texture loaded" << std::endl;
    }
}

//set the number of lives and update the heart sprites
void Health::setLives(int playerLives) {
    if (playerLives < heartSprites.size()) {
        heartSprites.resize(playerLives);
    }
    else if (playerLives > heartSprites.size()) {
        for (int i = heartSprites.size(); i < playerLives; ++i) {
            sf::Sprite heartSprite;
            heartSprite.setTexture(healthTexture);
            heartSprite.setTextureRect(sf::IntRect(0, 0, 16, 16)); //sprite coords
            heartSprite.setScale(2.f, 2.f);
            heartSprites.push_back(heartSprite);
        }
    }
}



//reposition hearts relative to the view
void Health::updatePosition(const sf::RenderWindow& window) {
    const sf::View& view = window.getView();
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    float startX = viewCenter.x - viewSize.x / 2.f + 10.f; //top left corner with 10px padding
    float startY = viewCenter.y - viewSize.y / 2.f + 10.f;

    for (int i = 0; i < heartSprites.size(); ++i) {
        heartSprites[i].setPosition(startX + i * 40.f, startY); //40px spacing between hearts
    }
}

//draw all heart sprites
void Health::draw(sf::RenderWindow& window) {
    for (const auto& heart : heartSprites) {
        window.draw(heart);
    }
}
