#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H
#include <iostream>
#include <string>
#include "tictactoe.h"

class TicTacToe;
class Menu {
	TicTacToe* game;
private:
	void sayBye();
	void printMenu();
	void printSettingsMenu();
	void setFieldSize();
	void setWinLength();
public:
	Menu();
	Menu(TicTacToe* game);
	void mainMenu();
	void settingsMenu();
};

#endif // !MAINMENU_H