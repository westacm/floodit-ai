//
// Created by Mitchell on 6/9/2021.
//

#ifndef FLOODIT_AI_MYAI_H
#define FLOODIT_AI_MYAI_H

#include "Player.h"
#include "BoardSimple.h"

class MyAI : public Player {
private:

public:
    MyAI(std::string n="My AI") : Player(n) { displayBoard = false; }

    bool getMove(BoardSimple board, int& colour, int& row, int& col);
};

/* == MyAI::getMove ==
 * params:
 * - board: A BoardSimple version of the current board state.
 * - colour, row, col: a reference to store the corresponding values of the move the AI
 *      wants to make.
 *
 * returns true on success, false on fail
 */
bool MyAI::getMove(BoardSimple board, int &colour, int &row, int &col) {



    return true;
}

#endif //FLOODIT_AI_MYAI_H
