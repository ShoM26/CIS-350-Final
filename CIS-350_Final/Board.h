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
	static const int boardSize = size + size;
	char board[boardSize][boardSize];
	vector<pair<int, int>> blockCords;

	bool populateBoard();
	int checkRow(int rowNum);
	int checkColumn(int colNum);
	bool addConnection(string wordOne, string wordTwo, int connectionPointOne, int connectionPointTwo);
	bool canPlaceHorizontally(int row, int col, string word);
	void placeHorizontally(int row, int col, string word);
	bool canPlaceVertically(int row, int col, string word);
	void placeVertically(int row, int col, string word);
	bool fillBoard(string name);
	bool addBlocks(int n);
	void padWithBlocks();
	void display();
};
