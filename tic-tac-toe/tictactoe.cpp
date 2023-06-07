#include "tictactoe.h"


TicTacToe::TicTacToe() {
	this->field_size = 3;
	this->win_length = 3;
	this->menu = new Menu(this);
	menu->mainMenu();
}

void TicTacToe::startGame() {
	gameInit();
}

void TicTacToe::gameInit() {
	std::cout << "=====================================================" << std::endl;
	std::cout << "            GAME HAS STARTED! GOOD LUCK!             " << std::endl;
	std::cout << "=====================================================" << std::endl;
	const int MINPLAYER = 1;
	const int MAXPLAYER = 2;
	int perm, nrow, ncol;
	bool finished = false;
	std::string field_number;
	showField(this->root->field_state);
	while (!finished){
		gameLoop(MINPLAYER, MAXPLAYER, perm, nrow, ncol, field_number, finished);
	}
}

bool TicTacToe::isOccupied(const std::vector<std::vector<int> >& field_state, const int& nrow, const int& ncol) {
	if (field_state[nrow][ncol] != 0) {
		return true;
	}
	return false;
}

void TicTacToe::gameLoop(const int& MINPLAYER, const int& MAXPLAYER, int& perm, int& nrow, int& ncol, std::string& field_number, bool& finished) {
	// add some protection against choosing wrong fields
	while (1) {
		std::cout << "Enter field number ('nrow,ncol'): ";
		std::cin >> field_number;
		nrow = std::stoi(field_number.substr(0, field_number.find(',')));
		ncol = std::stoi(field_number.substr(field_number.find(',') + 1, std::string::npos)); //field_size % 10 + 1
		if (isOccupied(root->field_state, nrow, ncol)) {
			std::cout << "This field is occupied. Try another." << std::endl;
			continue;
		}
		break;
	}
	root->field_state[nrow][ncol] = MINPLAYER;
	showField(root->field_state);

	perm = gameFinished(root->field_state);
	if (perm) {
		if (perm == 3) {
			std::cout << "IT'S A DRAW!" << std::endl;
		}
		else {
			std::cout << perm << " won the game!" << std::endl;
		}
		finished = true;
		return;
	}

	// debug. has some decision problems
	int value = minimax(root, 4, true, -1000, 1000);
	for (auto child : root->children) {
		if ((child != nullptr) && (child->heuristic_value == value)) {
			root->field_state = child->field_state;
			root->children.clear();
			break;
		}
	}

	showField(root->field_state);

	perm = gameFinished(root->field_state);
	if (perm) {
		if (perm == 3) {
			std::cout << "IT'S A DRAW!" << std::endl;
		}
		else {
			std::cout << perm << " won the game!" << std::endl;
		}
		finished = true;
		return;
	}
}

bool TicTacToe::hasNeighbours(const std::vector<std::vector<int> >& field_state, const int& nrow, const int& ncol) {
	for (int i = nrow-1; i <= nrow+1; i++) {
		for (int j = ncol-1; j <= ncol+1; j++) {
			if (!((i >= 0) && (i < field_size)) || !((j >= 0) && (j < field_size))) {
				continue;
			}
			if (field_state[i][j] != 0) {
				return true;
			}
		}
	}
	return false;
}

void TicTacToe::findAllChildren(GameState *gameState, bool maxPlayer){
	if (!gameState->children.empty()) {
		return;
	}
	int value = maxPlayer ? 2 : 1;
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			if (gameState->field_state[i][j] != 0) {
				continue;
			}
			if (!hasNeighbours(gameState->field_state, i, j)) {
				continue;
			}
			gameState->field_state[i][j] = value;
			gameState->children.push_back(new GameState(gameState));
			gameState->field_state[i][j] = 0;
		}
	}
}

int TicTacToe::stateEvaluation(const std::vector<std::vector<int> >& field_state, int depth, bool maxPlayer) {
	int weight = depth >= 0 ? depth : -depth;
	int result = gameFinished(field_state);
	if (result == 1) {
		return -60 + weight;
	}
	else if (result == 2) {
		return 70 - weight;
	}
	else {
		return -2 * weight;
	}
	return 0;
}
 

// nie rozpatrujemy kratek ktore nie maja sasiedzi
int TicTacToe::minimax(GameState* gameState, int depth, bool maxPlayer, int alpha, int beta) {
	if ((depth == 0) || gameFinished(gameState->field_state)) {
		gameState->heuristic_value = stateEvaluation(gameState->field_state, gameState->depth, maxPlayer);
		return gameState->heuristic_value;
	}

	if (maxPlayer) {
		int maxEvaluation = -1000;
		findAllChildren(gameState, true);
		for (auto child : gameState->children) {
			int evaluation = minimax(child, depth - 1, false, alpha, beta);
			maxEvaluation = maxEvaluation > evaluation ? maxEvaluation : evaluation;
			alpha = alpha > evaluation ? alpha : evaluation;
			if (beta <= alpha) {
				break;
			}
		}
		gameState->heuristic_value = maxEvaluation;
		return maxEvaluation;
	}
	else {
		int minEvaluation = 1000;
		findAllChildren(gameState, false);
		for (auto child : gameState->children) {
			int evaluation = minimax(child, depth - 1, true, alpha, beta);
			minEvaluation = minEvaluation < evaluation ? minEvaluation : evaluation;
			beta = beta < evaluation ? beta : evaluation;
			if (beta <= alpha) {
				break;
			}
		}
		gameState->heuristic_value = minEvaluation;
		return minEvaluation;
	}
}

bool TicTacToe::boardFull(const std::vector<std::vector<int> >& field_state){
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			if (field_state[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

int TicTacToe::gameFinished(const std::vector<std::vector<int> >& field_state) {

	int counter = 1;  // counter is 1 FROM STARTERS because first 'previous' is -1 anyway
	int previous = -1;
	int current;

	// check all horizontal possibilities
	for (int i = 0; i < field_size; i++) {
		counter = 1;
		previous = -1;
		for (int j = 0; j < field_size; j++) {
			current = field_state[i][j];

			if ( (current == previous) && (current != 0) ) {
				counter++;
			}
			else {
				counter = 1;
			}

			if (counter == win_length) {
				return current;
			}
			previous = current;
		}
	}

	// check all vertical possibilities
	for (int i = 0; i < field_size; i++) {
		counter = 1;
		previous = -1;
		for (int j = 0; j < field_size; j++) {
			current = field_state[j][i];

			if ((current == previous) && (current != 0)) {
				counter++;
			}
			else {
				counter = 1;
			}
			if (counter == win_length) {
				return current;
			}
			previous = current;
		}
	}

	int row, col;

	// =============== angle < 90 ========================
	for (int i = field_size - 1; i >= (win_length - 1); i--) {
		row = i;
		col = 0;
		counter = 1;
		previous = -1;
		while ((row >= 0) && (col < field_size)) {
			current = field_state[row][col];

			if ((current == previous) && (current != 0)) {
				counter++;
			}
			else {
				counter = 1;
			}
			if (counter == win_length) {
				return current;
			}
			previous = current;
			row--;
			col++;
		}

	}

	for (int i = 1; i < field_size; i++) {
		row = i;
		col = field_size - 1;
		counter = 1;
		previous = -1;
		while ((row < field_size) && (col >= 0)) {
			current = field_state[row][col];

			if ((current == previous) && (current != 0)) {
				counter++;
			}
			else {
				counter = 1;
			}
			if (counter == win_length) {
				return current;
			}
			previous = current;
			row++;
			col--;
		}
	}
	// ===============================================

	// =============== angle > 90 ====================

	for (int i = field_size - 1; i >= (win_length - 1); i--) {
		row = i;
		col = field_size - 1;
		counter = 1;
		previous = -1;
		while ((row >= 0) && (col >= 0)) {
			current = field_state[row][col];

			if ((current == previous) && (current != 0)) {
				counter++;
			}
			else {
				counter = 1;
			}
			if (counter == win_length) {
				return current;
			}
			previous = current;
			row--;
			col--;
		}

	}

	for (int i = 1; i < field_size; i++) {
		row = i;
		col = 0;
		counter = 1;
		previous = -1;
		while ((row < field_size) && (col >= 0)) {
			current = field_state[row][col];

			if ((current == previous) && (current != 0)) {
				counter++;
			}
			else {
				counter = 1;
			}
			if (counter == win_length) {
				return current;
			}
			previous = current;
			row++;
			col++;
		}
	}
	// ===============================================

	if (boardFull(field_state)) {
		return 3;
	}


	return 0; // game is not finished yet
}

void TicTacToe::showField(const std::vector<std::vector<int> >& field_state) {
	std::string hborder = "  " + std::string(4 * field_size + 1, '-');
	std::cout << "  ";
	for (int i = 0; i < field_size; i++) {
		std::cout << "  " << i << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < field_size; i++) {
		std::cout << hborder << std::endl;
		std::cout << i << " ";
		for (int j = 0; j < field_size; j++) {
			std::string value;
			if (field_state[i][j] == 0) {
				value = " ";
			}
			else if (field_state[i][j] == 1) {
				value = "X";
			}
			else if (field_state[i][j] == 2) {
				value = "O";
			}
			std::cout << "| " << value << " ";
		}
		std::cout << "|" << std::endl;
	}
	std::cout << hborder << std::endl;
}