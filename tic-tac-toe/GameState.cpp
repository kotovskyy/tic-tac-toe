#include "GameState.h"

GameState::GameState() {}

GameState::GameState(GameState* parent) {
	this->field_state = parent->field_state;
	this->parent = parent;
	this->depth = parent->depth - 1;
	this->heuristic_value = 0;
	this->maxPlayermove = !parent->maxPlayermove;
	this->children = std::vector<GameState*>();
}

GameState::GameState(std::vector<std::vector<int> > field_state) {
	this->field_state = field_state;
	this->depth = 0;
	this->heuristic_value = 0;
	this->maxPlayermove = false;
	this->parent = nullptr;
	this->children = std::vector<GameState*>();
}