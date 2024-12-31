#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Puzzle {
private:
    sf::Font font;             
    sf::Text problemText;        
    sf::Text inputText;          
    sf::Text feedbackText;       
    std::string playerInput;     
    int correctAnswer;           

    void generateMathProblem();  

public:
    Puzzle();
    bool run(sf::RenderWindow& window);
};

#endif
