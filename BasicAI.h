//
// Created by Mitchell on 6/6/2021.
//

#ifndef FLOODIT_AI_BASICAI_H
#define FLOODIT_AI_BASICAI_H

#include "Player.h"
#include "BoardSimple.h"

class BasicAI : public Player {
private:

public:
    BasicAI(std::string n="Basic AI") : Player(n) { displayBoard = true; }

    bool getMove(BoardSimple board, int& colour, int& row, int& col);
};

/* == BasicAI::getMove ==
 * Chooses it's moved based on the first colour it finds from left-right and top-bottom.
 * Row and col are always 0, it looks for the first colour which is not the same as the one at [0][0].
 */
bool BasicAI::getMove(BoardSimple board, int &colour, int &row, int &col) {

    int i = board.grid[0][0];
    for(int r = 0; r < board.width; r++) {
        for(int c = 0; c < board.height; c++) {
            if(board.grid[r][c] != i) {
                row = 0;
                col = 0;
                colour = board.grid[r][c];
                return true;
            }
        }
    }

    return false;
}

#endif //FLOODIT_AI_BASICAI_H
