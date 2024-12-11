#include "Options.hpp"

Options::Options(float width, float height) {
	if (!font.loadFromFile("fonts/joystix_monospace.otf")) {
		std::cout << "font not found" << std::endl;
	}

	//menu items
	//item 1
	optionsMenu[0].setFont(font);
	optionsMenu[0].setFillColor(sf::Color::White);
	optionsMenu[0].setString("Option 1");
	optionsMenu[0].setCharacterSize(70);
	optionsMenu[0].setPosition(200, 200);

	//item 2
	optionsMenu[1].setFont(font);
	optionsMenu[1].setFillColor(sf::Color::White);
	optionsMenu[1].setString("Option 2");
	optionsMenu[1].setCharacterSize(70);
	optionsMenu[1].setPosition(200, 300);

	//item 3
	optionsMenu[2].setFont(font);
	optionsMenu[2].setFillColor(sf::Color::White);
	optionsMenu[2].setString("Option 3");
	optionsMenu[2].setCharacterSize(70);
	optionsMenu[2].setPosition(200, 400);

	//item 4
	optionsMenu[3].setFont(font);
	optionsMenu[3].setFillColor(sf::Color::White);
	optionsMenu[3].setString("Return to Menu");
	optionsMenu[3].setCharacterSize(70);
	optionsMenu[3].setPosition(200, 500);

	OptionsSelected = -1;

}

Options::~Options() {
	std::cout << "Options destructor called" << std::endl;
	exit(0);
}

void Options::opDraw(sf::RenderWindow& window) {

	for (int i = 0; i < Max_options_menu; i++) {
		window.draw(optionsMenu[i]);
	}
}

void Options::opMoveUp() {
	optionsMenu[OptionsSelected].setFillColor(sf::Color::White); //reset current selection color

	if (OptionsSelected == 0) { //wrap to the last item
		OptionsSelected = Max_options_menu - 1;
	}
	else {
		OptionsSelected--; //decrement selection
	}

	optionsMenu[OptionsSelected].setFillColor(sf::Color::Blue); //highlight new selection
}

void Options::opMoveDown() {
	optionsMenu[OptionsSelected].setFillColor(sf::Color::White); //reset current selection color

	OptionsSelected++; //increment selection

	if (OptionsSelected >= Max_options_menu) { //wrap to the first item
		OptionsSelected = 0;
	}

	optionsMenu[OptionsSelected].setFillColor(sf::Color::Blue); //highlight new selection
}