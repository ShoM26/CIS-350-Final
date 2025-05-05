#include "Board.h"

char Board::randomChar()
{
	return 'A' + rand() % 26;
}

Board::Grid Board::randomInner()
{
	Grid grid(ROWS, vector<char>(COLS));
	for (int i = 0; i < ROWS; ++i)
		for (int j = 0; j < COLS; ++j)
			grid[i][j] = randomChar();
	return grid;
}

bool Board::inDataBase(string word)
{
	ifstream file;
	string parser;
	file.open("database.txt");
	if (file) {
		while (getline(file, parser)) {
			if (parser == word) {
				return true;
			}
		}
		return false;
	}
	else {
		cerr << "Could not open the database\n";
		return false;
	}
}

int Board::fitness(const Grid& grid)
{
	int fitnessScore = 0;
	string temp;
	string gridLetters;
	//switch statement for column first then rows
	for (int i = 1; i < 6; i++) {
		//left to right, top to bottom
		switch (i)
		{
		case 1:
			//gathering grid letters for first layer down
			for (int j = 0; j < COLS; j++) {
				gridLetters += grid[j][i-1];
			}
			temp = this->board[0][i] + gridLetters + this->board[size-1][i];
			if (inDataBase(temp)) {
				fitnessScore++;
			}
			break;
		case 2:
			for (int j = 0; j < COLS; j++) {
				gridLetters += grid[j][i-1];
			}
			temp = this->board[0][i] + gridLetters + this->board[size-1][i];
			if (inDataBase(temp)) {
				fitnessScore++;
			}
			break;
		case 3:
			for (int j = 0; j < COLS; j++) {
				gridLetters += grid[j][i - 1];
			}
			temp = this->board[0][i] + gridLetters + this->board[size-1][i];
			if (inDataBase(temp)) {
				fitnessScore++;
			}
			break;
		case 4:
			for (int j = 0; j < ROWS; j++) {
				gridLetters += grid[i-4][j];
			}
			temp = this->board[i-3][0] + gridLetters + this->board[i-3][size-1];
			if (inDataBase(temp)) {
				fitnessScore++;
			}
			break;
		case 5:
			for (int j = 0; j < ROWS; j++) {
				gridLetters += grid[i - 4][j];
			}
			temp = this->board[i - 3][0] + gridLetters + this->board[i - 3][size-1];
			if (inDataBase(temp)) {
				fitnessScore++;
			}
			break;
		case 6:
			for (int j = 0; j < ROWS; j++) {
				gridLetters += grid[i - 4][j];
			}
			temp = this->board[i - 3][0] + gridLetters + this->board[i - 3][size-1];
			if (inDataBase(temp)) {
				fitnessScore++;
			}
			break;
		default:
			cout << "Something went wrong\n";
			break;
		}
	}

	return fitnessScore;//if correct should return 6
}

Board::Grid Board::select(const std::vector<Grid>& population, const std::vector<int>& fitnesses)
{
	int totalFitness = 0;
	for (int f : fitnesses)
		totalFitness += f;

	int pick = rand() % (totalFitness + 1);
	int current = 0;

	for (size_t i = 0; i < population.size(); ++i) {
		current += fitnesses[i];
		if (current >= pick)
			return population[i];
	}

	return population[0]; // fallback
}

Board::Grid Board::mutate(const Grid& grid)
{
	Grid newGrid = grid;
	for (int i = 0; i < ROWS; ++i)
		for (int j = 0; j < COLS; ++j)
			if ((double)rand() / RAND_MAX < MUTATION_RATE)
				newGrid[i][j] = randomChar();
	return newGrid;
}

Board::Grid Board::crossover(const Grid& parent1, const Grid& parent2)
{
	Grid child(ROWS, vector<char>(COLS));
	for (int i = 0; i < ROWS; ++i)
		child[i] = (rand() % 2 == 0) ? parent1[i] : parent2[i];
	return child;
}

bool Board::populateBoard()
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = '#';
		}
	}
	return true;
}

void Board::printGrid(const Grid& grid)
{
	for (const auto& row : grid) {
		for (char c : row)
			std::cout << c;
		std::cout << '\n';
	}
}


bool Board::fillBorder()
{
	ifstream file;
	string word;
	int borderStep = 1;
	file.open("database.txt");
	if (file) {
		//cout << "No trouble opening the file\n"; //error testing
		while (getline(file, word)) {
			//Border Creation
			switch (borderStep) {
			case 1: // top row
				if (word.size() == size) {
					for (int c = 0; c < size; c++) {
						board[0][c] = word[c];
					}
					borderStep++;
				}
				break;

			case 2: // left column
				if (word.size() == size) {
					if (word[0] == board[0][0]) {
						for (int r = 1; r < size; r++) {
							board[r][0] = word[r];
						}
						borderStep++;
					}
				}
				break;

			case 3: // bottom row
			if(word.size() == size) {
				if (word[0] == board[size - 1][0]) {
					for (int c = 1; c < size; c++) {
						board[size - 1][c] = word[c];
					}
					borderStep++;
				}
			}
				break;

			case 4: // right column
			if(word.size() == size) {
				if (word[0] == board[0][size - 1] && word[size - 1] == board[size - 1][size - 1]) {
					for (int r = 1; r < size - 1; r++) {
						board[r][size - 1] = word[r];
					}
					borderStep++;
				}
			}
				break;
			default: // no more border to fill
				break;
			}
			file.close();
			return true;
		}
	}
	else {
		cerr << "An error has occured when trying to open your text file\n";
		return false;
	}
}


Board::Grid Board::fillCenter()
{
	for (int i = 0; i < GENERATIONS; i++) {
		vector<Grid> population(POP_SIZE);
		for (int i = 0; i < POP_SIZE; ++i) {
			population[i] = randomInner();
		}

		vector<int> fitnesses(POP_SIZE);
		for (int i = 0; i < POP_SIZE; ++i) {
			fitnesses[i] = fitness(population[i]);
		}
		int bestIdx = distance(fitnesses.begin(), max_element(fitnesses.begin(), fitnesses.end()));
		int bestFit = fitnesses[bestIdx];
		if (bestFit == 6) {
			return population[bestIdx];
		}
		vector<Grid> newPopulation;
		for (int i = 0; i < POP_SIZE; ++i) {
			Grid parent1 = select(population, fitnesses);
			Grid parent2 = select(population, fitnesses);
			Grid child = crossover(parent1, parent2);
			child = mutate(child);
			newPopulation.push_back(child);
		}

		population = newPopulation;
	}
}

bool Board::fillBoard()
{
	if (fillBorder()) {
		Grid inner = fillCenter();
		for (int i = 1; i < size; i++) {
			for (int j = 1; j < size; j++) {
				board[i][j] == inner[i - 1][j - 1];
			}
		}
	}
}

void Board::padWithBlocks()
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (this->board[i][j] == '#') {
				this->board[i][j] = '!';
			}
		}
	}
}

void Board::display()
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}
