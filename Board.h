//
// Created by Mitchell on 6/6/2021.
//

#ifndef FLOODIT_AI_BOARD_H
#define FLOODIT_AI_BOARD_H

#include <chrono>
#include <iostream>

class Board {
private:
    int width;
    int height;
    int colourCount;

    int** grid;
public:
    /* Initialise */
    Board(int seed=-1, int colours=6, int w=20, int h=20);

    /* Game Functionality */
    bool outOfBounds(int row, int col);
    bool isValidMove(int row, int col, int colour);
    bool makeMove(int row, int col, int colour);
    void floodFill(int row, int col, int initialColour, int newColour);
    bool checkWin();

    /* Output */
    void print();

    /* Getters */
    int getWidth() { return width; }
    int getHeight() { return height; }
    int getColourCount() { return colourCount; }
    int** getGrid() { return grid; }
};

/* == Board::Board ==
 * Initialises the board to state as determined by the seed (or random if seed==-1).
 */
Board::Board(int seed, int colours, int w, int h) {
    // Init props
    width = w;
    height = h;
    colourCount = colours;

    // Initialise seed
    if(seed == -1) seed = time(NULL);
    srand(seed);

    // Initialise the grid randomly
    grid = new int*[height];
    for(int row = 0; row < height; row++) {
        grid[row] = new int[width];

        for(int col = 0; col < width; col++) {
            grid[row][col] = rand() % colours;
        }
    }
}

/* == Board::outOfBounds ==
 * Returns true if the given position is out of bounds on the board, returns false otherwise.
 */
bool Board::outOfBounds(int row, int col) {
    return row < 0 || col < 0 || row >= height || col >= width;
}

/* == Board::isValidMove ==
 * Returns true if the given move is valid on the board.
 * False if;
 * -- the move is out of bounds OR
 * -- the position given is already the specified colour
 */
bool Board::isValidMove(int row, int col, int colour) {
    return !outOfBounds(row, col) && grid[row][col] != colour;
}

/* == Board::makeMove ==
 * Makes the given move on the board.
 * row, col: position on the board
 * colour: the NEW colour
 *
 * Returns true if the move was legal and successful.
 * Returns false if the move was illegal or unsuccessful.
 * -- Example: The colour of the grid at [row][col] cannot match colour - the move must make some meaningful change to the board
 * -- OR: The move was out of bounds.
 */
bool Board::makeMove(int row, int col, int colour) {
    // Player made an invalid move
    if(!isValidMove(row, col, colour)) return false;

    floodFill(row, col, grid[row][col], colour);

    return true;
}

/* == Board::floodFill ==
 * Flood fills from the specified position with the specified colour.
 *
 * Uses taxicab geometry - i.e., up, down, left, right are the only neighbours of a cell (distance 1 from the cell)
 * https://en.wikipedia.org/wiki/Taxicab_geometry
 */
void Board::floodFill(int row, int col, int initialColour, int newColour) {
    // Only flood to neighbours squares of the initial colour (and are not out of bounds)
    if(outOfBounds(row, col) || grid[row][col] != initialColour) return;

    grid[row][col] = newColour; // Fills the cell

    // For simplicity's sake:
    floodFill(row-1, col, initialColour, newColour); // up
    floodFill(row, col+1, initialColour, newColour); // right
    floodFill(row+1, col, initialColour, newColour); // down
    floodFill(row, col-1, initialColour, newColour); // left
}

/* == Board::checkWin ==
 * Returns true if the board is in the win state, false otherwise.
 * Win state is defined as the whole board being a uniform colour.
 */
bool Board::checkWin() {

    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width; col++) {
            if(grid[row][col] != grid[0][0]) return false;
        }
    }

    return true;
}

// TODO update print
/* == Board::print ==
 *
 * Prints the board to the screen. Feel free to modify this as you wish.
 */
void Board::print() {

    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width; col++) {
            std::cout << grid[row][col];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

#endif //FLOODIT_AI_BOARD_H
