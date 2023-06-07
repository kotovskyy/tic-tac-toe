#pragma once
#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <vector>

class GameState {
private:
	std::vector<std::vector<int> > field_state;  // current state of the game field
	int depth;                                   // how deep is that state in the game tree
	int heuristic_value;                         // what is his heuristic value
	bool maxPlayermove;                          // current move is maximazing player's
	GameState* parent;                           // parent in the game tree
	std::vector<GameState*> children;            // all moves which can be made in this field state
	friend class TicTacToe;
public:
	GameState();
	GameState(std::vector<std::vector<int> > field_state);
	GameState(GameState* parent);
};


#endif