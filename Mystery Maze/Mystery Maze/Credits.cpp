#include "Credits.hpp"
#include "MainMenu.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

void Credits::runCredits(sf::RenderWindow& window) {

    if (!font.loadFromFile("fonts/joystix_monospace.otf")) {
        std::cout << "font not found" << std::endl;
    }

    sf::Text creditsTitle("Credits:", font, 50);
    creditsTitle.setFillColor(sf::Color::White);
    creditsTitle.setPosition(60, 100);
    sf::Text creditsText("Tutorials Used:\nMenu Tutorial : YouTube.com/watch?v=bOG8667yePY\nScreen States : YouTube.com/watch?v=Qhlqhen6cmw\nViews Documentation : https://www.sfml-dev.org/tutorials/2.6/graphics-view.php\nGame Timer, score, and Game Music : https://cplusplus.com/forum/windows/172064/\nBounding box collision : https://www.youtube.com/watch?v=l2iCYCLi6MU\nHUD / UI : https ://www.youtube.com/watch?v=uqrcVITXtEM\nFont and text : https ://www.youtube.com/watch?v=8kuYOdRO894\nInput documentation : https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Keyboard.php\nTyping input : https://en.sfml-dev.org/forums/index.php?topic=26927.0 \n https://en.sfml-dev.org/forums/index.php?topic=19965.0\nSave to DAT : https://stackoverflow.com/questions/65104558/save-data-to-a-dat-file \n http://www.java2s.com/Tutorial/Cpp/0240__File-Stream/savespersonobjecttodisk.htm \n https://cplusplus.com/forum/beginner/106630/", font, 20);
    creditsText.setFillColor(sf::Color::White);
    creditsText.setPosition(60, 250);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) {
                return; //exit credits
            }
        }
        window.clear();
        window.draw(creditsText);
        window.draw(creditsTitle);
        window.display();
    }
}
