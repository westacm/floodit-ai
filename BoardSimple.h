//
// Created by Mitchell on 6/6/2021.
//

#ifndef FLOODIT_AI_BOARDSIMPLE_H
#define FLOODIT_AI_BOARDSIMPLE_H

/*
 * May be scrapped in the future! We are still experimenting.
 */
struct BoardSimple {
    // 2D grid representing the state of the board, where each value is the colour of the corresponding cell (from 0-[colourCount-1])
    int **grid;

    // Width, height, and colourCount (how many colours are on the board)
    int width, height, colourCount;

    BoardSimple(Board* b) {
        /* Copy basic properties */
        width = b->getWidth();
        height = b->getHeight();
        colourCount = b->getColourCount();

        /* Copy the values of the board's grid into the new one */
        int** g = b->getGrid();
        grid = new int*[height];

        for(int row = 0; row < height; row++) {
            grid[row] = new int[width];

            for(int col = 0; col < width; col++) {
                grid[row][col] = g[row][col];
            }
        }
    }

    /* == BoardSimple::outOfBounds ==
     * Returns true if the given position is out of bounds, false otherwise.
     */
    bool outOfBounds(int row, int col) {
        return row < 0 || col < 0 || row >= height || col >= width;
    }

    /* == BoardSimple::isValidMove ==
     * Returns true if the given move is valid on the board.
     * False if;
     * -- the move is out of bounds OR
     * -- the position given is already the specified colour
     */
    bool isValidMove(int row, int col, int colour) {
        return !outOfBounds(row, col) && grid[row][col] != colour;
    }
};

#endif //FLOODIT_AI_BOARDSIMPLE_H
