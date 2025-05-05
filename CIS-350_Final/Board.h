#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector> // Added
using namespace std;

class Board
{

	
public:
	static const int size = 5;
	char board[size][size];//First index is the row number then the column number
	char inner[size - 1][size - 1]; //inside
	using Grid = std::vector<std::vector<char>>;
	vector<pair<int, int>> blockCords;

	const int ROWS = size-1;
	const int COLS = size-1;
	const int POP_SIZE = 100;
	const int GENERATIONS = 1000;
	const double MUTATION_RATE = 0.05;

	//Function to generate a random char
	char randomChar();
	//Function to generate a random grid
	Grid randomInner(); //only to randomly generate the inner board
	//function to compute fitness score
	bool inDataBase(string word);
	int fitness(const Grid& grid);
	//Select function
	Grid select(const std::vector<Grid>& population, const std::vector<int>& fitnesses);
	//function to mutate
	Grid mutate(const Grid& grid);
	//crossover function
	Grid crossover(const Grid& parent1, const Grid& parent2);
	bool populateBoard();
	void printGrid(const Grid& grid);

	
	bool fillBorder(); //fills the border with size length words that work
	Grid fillCenter(); //genetic algorithm to determine one possible solution for the board
	bool fillBoard();
	void padWithBlocks(); //adds blocks after the board has been filled. This is the easy way out to lower complications
	void display();
};
