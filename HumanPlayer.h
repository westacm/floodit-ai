//
// Created by Mitchell on 6/6/2021.
//

#ifndef FLOODIT_AI_HUMANPLAYER_H
#define FLOODIT_AI_HUMANPLAYER_H

#include <iostream>

#include "Player.h"
#include "BoardSimple.h"

class HumanPlayer : public Player {
private:

public:
    HumanPlayer(std::string n="Human Player") : Player(n) { displayBoard = true; }

    bool getMove(BoardSimple board, int& colour, int& row, int& col);
};

/* == HumanPlayer::getMove ==
 * Gets the move as input from the user in the form "row col colour".
 */
bool HumanPlayer::getMove(BoardSimple board, int &colour, int &row, int &col) {

    while(!board.isValidMove(row, col, colour)) {
        std::cout << "Enter in a row, col, and colour in that order: \n";
        std::cin >> row >> col >> colour;
    }

    return true;
}

#endif //FLOODIT_AI_HUMANPLAYER_H
