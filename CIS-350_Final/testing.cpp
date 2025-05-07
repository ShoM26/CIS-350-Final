#include "Board.h"

int main() {
    Board b;

    if (!b.fillBorder()) {
        cout << "Failed to fill board border" << endl;
        return 1;
    }

    // Fill the inner board using the genetic algorithm
    Board::Grid inner = b.fillCenter();
    if (inner.empty()) {
        cout << "Failed to fill center" << endl;
        return 1;
    }

    // Copy the inner grid into the main board (excluding borders)
    for (int r = 1; r < Board::size - 1; r++) {
        for (int c = 1; c < Board::size - 1; c++) {
            b.board[r][c] = inner[r - 1][c - 1];
        }
    }

    b.padWithBlocks(); // Optional: Add blocks if needed

    b.display(); // Display final result
    return 0;
}
