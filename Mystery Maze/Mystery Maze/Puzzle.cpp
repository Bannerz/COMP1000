#include "Puzzle.hpp"
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Puzzle::Puzzle() {
    //load font
    if (!font.loadFromFile("fonts/joystix_monospace.otf")) {
        std::cerr << "Font file not found!" << std::endl;
        exit(EXIT_FAILURE);
    }

    //initialise problem text
    problemText.setFont(font);
    problemText.setCharacterSize(40);
    problemText.setFillColor(sf::Color::White);
    problemText.setPosition(100, 100);

    //initialise input text
    inputText.setFont(font);
    inputText.setCharacterSize(40);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(100, 200);

    //initialise feedback text
    feedbackText.setFont(font);
    feedbackText.setCharacterSize(40);
    feedbackText.setFillColor(sf::Color::Green);
    feedbackText.setPosition(100, 300);

    //generate a random math problem
    generateMathProblem();
}

void Puzzle::generateMathProblem() {
    srand(static_cast<unsigned>(time(0)));
    int num1 = rand() % 10 + 1;  //random number between 1 and 10
    int num2 = rand() % 10 + 1;  //random number between 1 and 10

    std::ostringstream oss;
    oss << "Solve: " << num1 << " + " << num2;
    problemText.setString(oss.str());

    correctAnswer = num1 + num2; //store the correct answer
}

bool Puzzle::run(sf::RenderWindow& window) {
    //save the current view
    sf::View originalView = window.getView();

    //create and set a static view for the puzzle screen
    sf::View puzzleView(sf::FloatRect(0, 0, 800, 600)); //adjust dimensions as needed
    puzzleView.setCenter(400, 300); //center the view on the puzzle screen area
    window.setView(puzzleView);

    sf::Event event;
    playerInput.clear();
    feedbackText.setString(""); //clear feedback

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }

            //exit to menu on Escape key
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
                puzzleView.setCenter(800.f, 800.f); //move the view back to original position so the menu doesn't move
                window.setView(puzzleView); //set the view
                return true; //actually return to previous menu
            }

            inputText.setString("Your Answer: " + playerInput);

            if (event.type == sf::Event::TextEntered) {
                //handle numeric input
                if (std::isdigit(event.text.unicode)) {
                    playerInput += static_cast<char>(event.text.unicode);
                    inputText.setString("Your Answer: " + playerInput);
                }

                //handle backspace
                if (event.text.unicode == 8 && !playerInput.empty()) { //8 is backspace
                    playerInput.pop_back();
                    inputText.setString("Your Answer: " + playerInput);
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                //check the player's answer
                if (!playerInput.empty() && std::stoi(playerInput) == correctAnswer) {
                    feedbackText.setString("Correct!");
                    window.clear();
                    window.draw(problemText);
                    window.draw(inputText);
                    window.draw(feedbackText);
                    window.display();
                    sf::sleep(sf::seconds(1)); //pause for feedback

                    //restore the original view before returning
                    window.setView(originalView);
                    return true; //answer is correct
                }
                else {
                    feedbackText.setString("Try Again!");
                }
            }
        }

        //render the puzzle screen
        window.clear();
        window.draw(problemText);
        window.draw(inputText);
        window.draw(feedbackText);
        window.display();
    }

    //restore the original view if the puzzle screen is exited
    window.setView(originalView);
    return false;
}

