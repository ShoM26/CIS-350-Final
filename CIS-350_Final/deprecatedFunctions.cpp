
int Board::checkRow(int rowNum)
{
	int counter = 0;
	for (int j = 0; j < size; j++) {
		if (board[rowNum][j] == '#') {
			counter++;
		}
	}
	return counter;
}

int Board::checkColumn(int colNum)
{
	int counter = 0;
	for (int i = 0; i < size; i++) {
		if (board[i][colNum] == '#') {
			counter++;
		}
	}
	return counter;
}
bool Board::addBlocks(int n)
{
	pair<int, int> cords;
	bool tflag = false;
	int c; int r;
	int min = 0;
	int max = size;
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




bool Board::fillBorder()
{
	ifstream file;
	string word;
	vector<string> misfit;
	file.open("database.txt");
	if (file) {
		//cout << "No trouble opening the file\n"; //error testing
		while (getline(file, word)) {
			//Boarder Creation
			if (this->board[0][0] == '#') {
				if (word.size() == size) {
					for (int c = 0; c < size; c++) {
						board[0][c] = word[c];
					}
				}
				else {
					misfit.push_back(word);
				}
			}
			else if (this->board[1][0] == '#') {
				if (word.size() == size) {
					if (word[0] == board[0][0]) {
						for (int r = 0; r < size; r++) {
							board[r][0] = word[r];
						}
					}
					else {
						misfit.push_back(word);
					}
				}
				else {
					misfit.push_back(word);
				}
			}
			else if (this->board[size - 1][1] == '#') {
				if (word.size() == size) {
					if (word[0] == board[size - 1][0]) {
						for (int c = 0; c < size; c++) {
							board[size - 1][c] = word[c];
						}
					}
					else {
						misfit.push_back(word);
					}
				}
				else {
					misfit.push_back(word);
				}
			}
			else if (this->board[1][size - 1] == '#') {
				if (word.size() == size) {
					if (word[0] == board[0][size - 1] && word[size - 1] == board[size - 1][size - 1]) {
						for (int r = 0; r < size; r++) {
							board[r][size - 1] = word[r];
						}
					}
					else {
						misfit.push_back(word);
					}
				}
				else {
					misfit.push_back(word);
				}
			}
		}
		file.close();
		return true;
	}
	else {
		cerr << "An error has occured when trying to open your text file\n";
		return false;
	}
}