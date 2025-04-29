#include "Board.h"

int main() {

	string word = "happe";
	char arr[5];
	cout << sizeof(word) << endl;
	cout << sizeof(arr);






	Board myBoard;
	myBoard.populateBoard();
	myBoard.display();
	myBoard.addBlocks(2);
	myBoard.display();

	myBoard.fillBoard("sampleCross.txt");

	return 0;
}