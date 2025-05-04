#include "Board.h"

bool Board::populateBoard()
{
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			board[i][j] = '#';
		}
	}
	return true;
}

int Board::checkRow(int rowNum)
{
	int counter = 0;
	for (int j = 0; j < boardSize; j++) {
		if (board[rowNum][j] == '#') {
			counter++;
		}
	}
	return counter;
}

int Board::checkColumn(int colNum)
{
	int counter = 0;
	for (int i = 0; i < boardSize; i++) {
		if (board[i][colNum] == '#') {
			counter++;
		}
	}
	return counter;
}

bool Board::addConnection(string wordOne, string wordTwo, int connectionPointOne, int connectionPointTwo)
{
	return false;
}

bool Board::canPlaceHorizontally(int row, int col, string word) {
	if (col + word.size() > boardSize) return false;
	for (int i = 0; i < word.size(); ++i) {
		char ch = board[row][col + i];
		if (ch != '#' && ch != word[i]) return false;
	}
	return true;
}

void Board::placeHorizontally(int row, int col, string word) {
	for (int i = 0; i < word.size(); ++i) {
		board[row][col + i] = word[i];
	}
}

bool Board::canPlaceVertically(int row, int col, string word) {
	if (row + word.size() > boardSize) return false;
	for (int i = 0; i < word.size(); ++i) {
		char ch = board[row + i][col];
		if (ch != '#' && ch != word[i]) return false;
	}
	return true;
}

void Board::placeVertically(int row, int col, string word) {
	for (int i = 0; i < word.size(); ++i) {
		board[row + i][col] = word[i];
	}
}

bool Board::fillBoard(string name)
{
	ifstream file;
	cout << "Trying to open: " << name << endl;
	string word;
	vector<string> misfit;
	file.open(name);

	if (file) {
		int borderStep = 0;
		while (getline(file, word)) {
			cout << "Read word: " << word << endl;

			// If the word does not match the size of the board, add to misfit
			if (word.length() != size) {
				misfit.push_back(word);
				continue;
			}

			
			switch (borderStep) {
			case 0: // top row
				for (int c = 0; c < size; c++) {
					board[0][c] = word[c];
				}
				break;

			case 1: // left column
				if (word[0] != board[0][0]) {
					misfit.push_back(word);
					continue;
				}
				for (int r = 1; r < size; r++) {
					board[r][0] = word[r];
				}
				break;

			case 2: // bottom row
				if (word[0] != board[size - 1][0]) {
					misfit.push_back(word);
					continue;
				}
				for (int c = 1; c < size; c++) {
					board[size - 1][c] = word[c];
				}
				break;

			case 3: // right column
				if (word[0] != board[0][size - 1] || word[size - 1] != board[size - 1][size - 1]) {
					misfit.push_back(word);
					continue;
				}
				for (int r = 1; r < size - 1; r++) {
					board[r][size - 1] = word[r];
				}
				break;

			default: // no more border to fill
				misfit.push_back(word);
				break;
			}

			borderStep++;
		}
		file.close();

	
		for (const string& word : misfit) {
			bool placed = false;
			for (int r = 0; r < boardSize && !placed; ++r) {
				for (int c = 0; c < boardSize && !placed; ++c) {
					if (canPlaceHorizontally(r, c, word)) {
						placeHorizontally(r, c, word);
						placed = true;
					}
					else if (canPlaceVertically(r, c, word)) {
						placeVertically(r, c, word);
						placed = true;
					}
				}
			}
			if (!placed) {
				cout << "Could not place word: " << word << endl;
			}
		}

		return true;
	}
	else {
		cerr << "An error has occurred when trying to open your text file\n";
		return false;
	}
}

bool Board::addBlocks(int n)
{
	pair<int, int> cords;
	bool tflag = false;
	int c; int r;
	int min = 0;
	int max = boardSize;
	for (int i = 0; i < n; i++) {
		c = (rand() % (max - min + 1));
		r = (rand() % (max - min + 1));
		if (this->board[r][c] == '!') {
			while (!tflag) {
				c = (rand() % (max - min + 1));
				r = (rand() % (max - min + 1));
				if (!(board[r][c] == '!')) {
					board[r][c] = '!';
					cords.first = r;
					cords.second = c;
					this->blockCords.push_back(cords);
					tflag = true;
				}
			}
		}
		else {
			this->board[r][c] = '!';
			cords.first = r;
			cords.second = c;
			this->blockCords.push_back(cords);
		}
	}
	return true;
}

void Board::padWithBlocks()
{
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (this->board[i][j] == '#') {
				this->board[i][j] = '!';
			}
		}
	}
}

void Board::display()
{
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

