#pragma once
#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H
#include "GameState.h"
#include "mainMenu.h"

class Menu;

class TicTacToe {
private:
	GameState* root;    // main game state
	int field_size;     // size of field : field_size X field_size
	int win_length;     // number of fields you need to fill in order to win
	Menu* menu;         // object of main menu for the game
	friend class Menu;
private:
	void gameLoop(const int& MINPLAYER, const int& MAXPLAYER, int& perm, int& nrow, int& ncol, std::string& field_number, bool& finished);
	void gameInit();
	void showField(const std::vector<std::vector<int> >& field_state);
	int gameFinished(const std::vector<std::vector<int> >& field_state);
	bool boardFull(const std::vector<std::vector<int> >& field_state);
	int minimax(GameState* gameState, int depth, bool maxPlayer, int alpha, int beta);
	int stateEvaluation(const std::vector<std::vector<int> >& field_state, int depth, bool maxPlayer);
	void findAllChildren(GameState* gameState, bool maxPlayer);
	bool isOccupied(const std::vector<std::vector<int> >& field_state, const int& nrow, const int& ncol);
	bool hasNeighbours(const std::vector<std::vector<int> >& field_state, const int& nrow, const int& ncol);
public:
	TicTacToe();
	void startGame();
};

#endif