#include "MainMenu.hpp"

MainMenu::MainMenu(float width, float height) {
	if (!font.loadFromFile("fonts/joystix_monospace.otf")) {
		std::cout << "font not found" << std::endl;
	}
	//menu items
	//item 1
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::White);
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(200, 200);
	//item 2
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::White);
	mainMenu[1].setString("Options");
	mainMenu[1].setCharacterSize(70);
	mainMenu[1].setPosition(200, 300);
	//item 3
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::White);
	mainMenu[2].setString("Credits");
	mainMenu[2].setCharacterSize(70);
	mainMenu[2].setPosition(200, 400);
	//item 4
	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(sf::Color::White);
	mainMenu[3].setString("Exit");
	mainMenu[3].setCharacterSize(70);
	mainMenu[3].setPosition(200, 500);
	//default to unselected before user moves
	MainMenuSelected = -1;
}

MainMenu::~MainMenu() {
	std::cout << "MainMenu destructor called" << std::endl;
	exit(0);
}

void MainMenu::draw(sf::RenderWindow& window) {

	for (int i = 0; i < Max_main_menu; i++) {
		window.draw(mainMenu[i]);
	}
}

void MainMenu::MoveUp() {
	mainMenu[MainMenuSelected].setFillColor(sf::Color::White); //reset current selection color

	if (MainMenuSelected == 0) { //wrap to the last item
		MainMenuSelected = Max_main_menu - 1;
	}
	else {
		MainMenuSelected--; //decrement selection
	}

	mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue); //highlight new selection
}

void MainMenu::MoveDown() {
	mainMenu[MainMenuSelected].setFillColor(sf::Color::White); //reset current selection color

	MainMenuSelected++; //increment selection

	if (MainMenuSelected >= Max_main_menu) { //wrap to the first item
		MainMenuSelected = 0;
	}

	mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue); //highlight new selection
}