#include "mainMenu.h"


Menu::Menu(TicTacToe *game) {
	this->game = game;
}

void Menu::mainMenu() {
	int choice;
	bool endGame = false;
	while (!endGame) {
		printMenu();
		std::cout << "Enter your choice (1/2/3): ";
		std::cin >> choice;
		std::cout << std::endl;

		if (choice == 1) {
			game->root = new GameState(std::vector<std::vector<int> >(game->field_size, std::vector<int>(game->field_size, 0)));
			game->startGame();
		}
		else if (choice == 2) {
			settingsMenu();
		}
		else if (choice == 3) {
			sayBye();
			endGame = true;
		}
		else {
			std::cout << "There is no such option. Try again!" << std::endl;
		}
	}
}

void Menu::settingsMenu() {
	int choice;
	bool correct = false;

	while (!correct) {
		printSettingsMenu();
		std::cout << "Enter your choice (1/2/3): ";
		std::cin >> choice;
		std::cout << std::endl;
		if (choice == 1) {
			setFieldSize();
		}
		else if (choice == 2) {
			setWinLength();
		}
		else if (choice == 3) {
			break;
		}
		else {
			std::cout << "There is no such option. Try again!" << std::endl;
		}
	}
}

void Menu::printMenu() {
	std::cout << "=====================================================" << std::endl;
	std::cout << "HELLO DEAR PLAYER! ARE YOU READY TO PLAY TIC-TAC-TOE?" << std::endl;
	std::cout << "=====================================================" << std::endl;
	std::cout << "1. Yes, I'm ready!                (START)" << std::endl;
	std::cout << "2. Wait, I've to change something (SETTINGS)" << std::endl;
	std::cout << "3. No, not now...                 (EXIT)" << std::endl;
	std::cout << "=====================================================" << std::endl;
}

void Menu::printSettingsMenu() {
	std::cout << "=========================================================" << std::endl;
	std::cout << "YOU ARE IN THE SETTINGS MENU. WHAT DO YOU WANT TO CHANGE?" << std::endl;
	std::cout << "=========================================================" << std::endl;
	std::cout << "1. Field Size              (current is " << game->field_size << ")" << std::endl;
	std::cout << "2. Number of Fields To Win (current is " << game->win_length << ")" << std::endl;
	std::cout << "3. Back to Main Menu" << std::endl;
	std::cout << "=====================================================" << std::endl;
}


void Menu::sayBye() {
	std::cout << "=====================================================" << std::endl;
	std::cout << "SEE YOU SOON! CHIAO, AMIGO!" << std::endl;
	std::cout << "=====================================================" << std::endl;
}

void Menu::setFieldSize() {
	int newval;
	bool correct = false;
	while (!correct) {
		std::cout << "Enter new FIELD SIZE (default 3): ";
		std::cin >> newval;
		if (newval < 3) {
			std::cout << std::endl << "Game field of size " << newval << "x" << newval << " doesn't make any sense. Try another!" << std::endl;
			continue;
		}
		game->field_size = newval;
		correct = true;
	}
}

void Menu::setWinLength() {
	// win_length can't be more than field size!!!

	int newval;
	bool correct = false;
	while (!correct) {
		std::cout << "Enter new FIELDS-TO-WIN (default 3): ";
		std::cin >> newval;
		if (newval < 3) {
			std::cout << std::endl << "Win with " << newval << " fields in a row doesn't make any sense. Try greater!" << std::endl;
			continue;
		}
		game->win_length = newval;
		correct = true;
	}
}