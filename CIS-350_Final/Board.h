#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <string>

using namespace std;

class Board
{
public:
	static const int size = 4;
	char board[size][size];//First index is the row number then the column number
	vector<pair<int, int>> blockCords;

	bool populateBoard();
	int checkRow(int rowNum); //takes a row to check and returns the number of empty spaces in the row
	int checkColumn(int colNum); //takes a column to check and returns the number of empty spaces in the column
	bool addConnection(string wordOne, string wordTwo, int connectionPointOne, int connectionPointTwo);
	bool fillBoard(string name); //sends the name/path of the file with the database to fill the board
	bool addBlocks(int n); //adds blocks randomly. meant to do before filling the board for a challange of the system.
	void padWithBlocks(); //adds blocks after the board has been filled. This is the easy way out to lower complications
	void display();
};

