#include "Board.h"

char Board::randomChar() {
    return 'A' + rand() % 26;
}

Board::Grid Board::randomInner() {
    Grid grid(ROWS, vector<char>(COLS));
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLS; ++j)
            grid[i][j] = randomChar();
    return grid;
}

bool Board::inDataBase(string word) {
    ifstream file(R"(C:\Users\ismai\source\repos\WorkFor\WorkFor\SampleCross.txt)");
    string parser;
    if (file) {
        while (getline(file, parser)) {
            if (parser == word)
                return true;
        }
    }
    else {
        cerr << "Could not open the database\n";
    }
    return false;
}

int Board::fitness(const Grid& grid) {
    int fitnessScore = 0;
    string temp;
    string gridLetters;
    for (int i = 1; i <= 6; i++) {
        gridLetters.clear();
        switch (i) {
        case 1: case 2: case 3:
            for (int j = 0; j < COLS; j++) {
                gridLetters += grid[j][i - 1];
            }
            temp = board[0][i] + gridLetters + board[size - 1][i];
            if (inDataBase(temp)) fitnessScore++;
            break;
        case 4: case 5:case 6:
            for (int j = 0; j < ROWS; j++) {
                gridLetters += grid[i - 4][j];
            }
            temp = board[i - 3][0] + gridLetters + board[i - 3][size - 1];
            if (inDataBase(temp)) fitnessScore++;
            break;
        default:
            cout << "Something went wrong\n";
            break;
        }
    }
    return fitnessScore;
}

Board::Grid Board::select(const std::vector<Grid>& population, const std::vector<int>& fitnesses) {
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
    return population[0];
}

Board::Grid Board::mutate(const Grid& grid) {
    Grid newGrid = grid;
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLS; ++j)
            if ((double)rand() / RAND_MAX < MUTATION_RATE)
                newGrid[i][j] = randomChar();
    return newGrid;
}

Board::Grid Board::crossover(const Grid& parent1, const Grid& parent2) {
    Grid child(ROWS, vector<char>(COLS));
    for (int i = 0; i < ROWS; ++i)
        child[i] = (rand() % 2 == 0) ? parent1[i] : parent2[i];
    return child;
}

bool Board::populateBoard() {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = '#';
    return true;
}

void Board::printGrid(const Grid& grid) {
    for (const auto& row : grid) {
        for (char c : row)
            cout << c;
        cout << '\n';
    }
}

bool Board::fillBorder() {
    populateBoard();
    ifstream file(R"(C:\Users\ismai\source\repos\WorkFor\WorkFor\SampleCross.txt)");
    string word;
    int borderStep = 1;

    if (!file) {
        cerr << "An error has occurred when trying to open your text file\n";
        return false;
    }

    while (getline(file, word)) {
        // Remove whitespace just in case
        word.erase(remove_if(word.begin(), word.end(), ::isspace), word.end());

        switch (borderStep) {
        case 1:  // Top row
            if (word.size() == size) {
                for (int c = 0; c < size; c++)
                    board[0][c] = word[c];
                cout << "Top row filled with: " << word << endl;
                borderStep++;
            }
            break;

        case 2:  // Left column
            if (word.size() == size && word[0] == board[0][0]) {
                for (int r = 1; r < size; r++)
                    board[r][0] = word[r];
                cout << "Left column filled with: " << word << endl;
                borderStep++;
            }
            break;

        case 3:  // Bottom row
            if (word.size() == size && word[0] == board[size - 1][0]) {
                for (int c = 1; c < size; c++)
                    board[size - 1][c] = word[c];
                cout << "Bottom row filled with: " << word << endl;
                borderStep++;
            }
            break;

        case 4:  // Right column
            if (word.size() == size &&
                word[0] == board[0][size - 1] &&
                word[size - 1] == board[size - 1][size - 1]) {

             /*   cout << "Trying to match right column with word: " << word << endl;*/
      /*          cout << "Expecting start: " << board[0][size - 1] << ", end: " << board[size - 1][size - 1] << endl;*/

                for (int r = 1; r < size - 1; r++) {
                    board[r][size - 1] = word[r];
                }

                cout << "Right column filled with: " << word << endl;
                borderStep++;
            }
            break;
        }

        if (borderStep > 4)
            break;
    }

    file.close();
    return borderStep > 4;
}

Board::Grid Board::fillCenter() {
    vector<Grid> population(POP_SIZE);
    for (int i = 0; i < POP_SIZE; ++i)
        population[i] = randomInner();

    for (int i = 0; i < GENERATIONS; i++) {
        vector<int> fitnesses(POP_SIZE);
        for (int j = 0; j < POP_SIZE; ++j)
            fitnesses[j] = fitness(population[j]);

        int bestIdx = distance(fitnesses.begin(), max_element(fitnesses.begin(), fitnesses.end()));
        int bestFit = fitnesses[bestIdx];
        if (bestFit == 6)
            return population[bestIdx];

        vector<Grid> newPopulation;
        for (int j = 0; j < POP_SIZE; ++j) {
            Grid parent1 = select(population, fitnesses);
            Grid parent2 = select(population, fitnesses);
            Grid child = crossover(parent1, parent2);
            newPopulation.push_back(mutate(child));
        }
        population = newPopulation;
    }
    return population[0];
}

bool Board::fillBoard() {
    if (fillBorder()) {
        Grid inner = fillCenter();
        for (int i = 1; i < size; i++)
            for (int j = 1; j < size; j++)
                board[i][j] = inner[i - 1][j - 1];
        return true;
    }
    return false;
}

void Board::padWithBlocks() {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == '#')
                board[i][j] = '!';
}

void Board::display() {
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            cout << board[r][c] << ' ';
        }
        cout << endl;
    }
}
